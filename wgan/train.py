#@title Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# https://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

from operator import ge
import tensorflow as tf
from tensorflow import keras
from tensorflow.python.keras.backend import sigmoid
from tensorflow.python.keras.layers.core import Activation, Flatten

tf.__version__

import glob
import matplotlib.pyplot as plt
import numpy as np
import os
import PIL
from tensorflow.keras import layers
import time

from board_operations import *

BATCH_SIZE = 32
IMAGE_SIZE = (7, 7)
NUMBER_OF_TILE_TYPES = 7
DATASET_PATH = "all_datasets/numpy_images.npy"


#TESTING SHUFFLE AND STUFF
#BUFFER_SIZE = 1000
#dataset = dataset.shuffle(4 * BATCH_SIZE)


#dataset = dataset.shuffle(1000)#.batch(BATCH_SIZE)

def make_generator_model():
    model = tf.keras.Sequential()
    model.add(layers.Dense(1*1*128, use_bias=False, input_shape=(100,)))
    model.add(layers.BatchNormalization())
    model.add(layers.LeakyReLU(alpha=0.2))

    model.add(layers.Reshape((1, 1, 128)))
    assert model.output_shape == (None, 1, 1, 128)

    model.add(layers.Conv2DTranspose(128, (5, 5)))
    model.add(layers.BatchNormalization())
    model.add(layers.LeakyReLU(alpha=0.2))

    model.add(layers.Conv2D(128, (3, 3), padding='same'))
    model.add(layers.BatchNormalization())
    model.add(layers.LeakyReLU(alpha=0.2))

    model.add(layers.Conv2DTranspose(64, (3, 3)))
    model.add(layers.BatchNormalization())
    model.add(layers.LeakyReLU(alpha=0.2))

    model.add(layers.Conv2D(64, (3, 3), padding='same'))
    model.add(layers.BatchNormalization())
    model.add(layers.LeakyReLU(alpha=0.2))

    model.add(layers.Conv2D(32, (3, 3), padding='same'))
    model.add(layers.BatchNormalization())
    model.add(layers.LeakyReLU(alpha=0.2))

    model.add(layers.Conv2D(NUMBER_OF_TILE_TYPES, (3, 3), padding='same'))
    model.add(layers.BatchNormalization())
    model.add(layers.LeakyReLU(alpha=0.2))
    model.add(layers.Softmax())
    #model.add(layers.Softmax())

    assert model.output_shape == (None, 7, 7, NUMBER_OF_TILE_TYPES)

    return model

def make_discriminator_model():
    model = tf.keras.Sequential()
    model.add(layers.Conv2D(NUMBER_OF_TILE_TYPES, (3, 3), padding='same', input_shape=[7, 7, NUMBER_OF_TILE_TYPES]))
    model.add(layers.LayerNormalization())
    model.add(layers.LeakyReLU(alpha=0.2))

    model.add(layers.Conv2D(32, (3, 3), padding='same'))
    model.add(layers.LayerNormalization())
    #model.add(layers.BatchNormalization()) # SWITCHED TO LAYERNORM SINCE WGAN DOES NOT ACCEPT BATCHNORM
    model.add(layers.LeakyReLU(alpha=0.2))

    model.add(layers.Conv2D(32, (3, 3), padding='same'))
    model.add(layers.LayerNormalization())
    #model.add(layers.BatchNormalization()) # SWITCHED TO LAYERNORM SINCE WGAN DOES NOT ACCEPT BATCHNORM
    model.add(layers.LeakyReLU(alpha=0.2))

    model.add(layers.Conv2D(64, (3, 3), padding='same'))
    model.add(layers.LayerNormalization())
    #model.add(layers.BatchNormalization()) # SWITCHED TO LAYERNORM SINCE WGAN DOES NOT ACCEPT BATCHNORM
    model.add(layers.LeakyReLU(alpha=0.2))

    model.add(layers.Conv2D(64, (3, 3)))
    model.add(layers.LayerNormalization())
    #model.add(layers.BatchNormalization())
    model.add(layers.LeakyReLU(alpha=0.2))

    model.add(layers.Conv2D(128, (3, 3), padding='same'))
    model.add(layers.LayerNormalization())
    #model.add(layers.BatchNormalization())
    model.add(layers.LeakyReLU(alpha=0.2))

    model.add(layers.Conv2D(128, (5, 5)))
    model.add(layers.LeakyReLU(alpha=0.2))
    model.add(layers.Flatten())

    model.add(layers.Dense(1))
    #model.add(layers.Activation(activation="sigmoid"))   
    #model.add(layers.Activation(activation="sigmoid"))   
    #model.add(layers.LeakyReLU(alpha=0.2))

#    model.add(layers.Flatten())
#
#    model.add(layers.Dense(32))
#    model.add(layers.BatchNormalization())
#    model.add(layers.LeakyReLU(alpha=0.2))
#    model.add(layers.Dense(1))

    return model

generator = make_generator_model()
discriminator = make_discriminator_model()

generator.summary()
discriminator.summary()

# This method returns a helper function to compute cross entropy loss
cross_entropy = tf.keras.losses.BinaryCrossentropy(from_logits=True)

counter = 0
def discriminator_loss(real_output, fake_output):
    real_loss = tf.reduce_mean(real_output)
    fake_loss = tf.reduce_mean(fake_output)
    return fake_loss - real_loss

def generator_loss(fake_output):
    return -tf.reduce_mean(fake_output)

generator_optimizer = tf.keras.optimizers.Adam(learning_rate=1e-5, beta_1=0.5, beta_2=0.9)
discriminator_optimizer = tf.keras.optimizers.Adam(learning_rate=1e-5, beta_1=0.5, beta_2=0.9)

checkpoint_dir = './training_checkpoints'
checkpoint_prefix = os.path.join(checkpoint_dir, "ckpt")
checkpoint = tf.train.Checkpoint(generator_optimizer=generator_optimizer,
                                 discriminator_optimizer=discriminator_optimizer,
                                 generator=generator,
                                 discriminator=discriminator)

EPOCHS = 100000
noise_dim = 100
num_examples_to_generate = 100

valid = 0

random_generator = tf.random.Generator.from_non_deterministic_state()

def gradient_penalty(batch_size, real_images, fake_images):
    alpha = tf.random.normal([batch_size, 1, 1, 1], 0.0, 1.0)
    diff = fake_images - real_images

    interpolated = real_images + alpha * diff

    with tf.GradientTape() as gp_tape:
        gp_tape.watch(interpolated)

        pred = discriminator(interpolated, training=True)

    grads = gp_tape.gradient(pred, [interpolated])[0]
    norm = tf.sqrt(tf.reduce_sum(tf.square(grads), axis=[1, 2, 3]))
    gp = tf.reduce_mean((norm - 1.0) ** 2)

    return gp

GP_WEIGHT = 10.0
D_STEPS = 8

# Notice the use of `tf.function`
# This annotation causes the function to be "compiled".
@tf.function
def train_step_disc(real_images):

    noise = random_generator.normal([BATCH_SIZE, noise_dim])
    with tf.GradientTape() as tape:
        fake_images = generator(noise, training=True)
        # Get the logits for the fake images
        fake_logits = discriminator(fake_images, training=True)
        # Get the logits for the real images
        real_logits = discriminator(real_images, training=True)

        disc_cost = discriminator_loss(real_logits, fake_logits)

        gp = gradient_penalty(BATCH_SIZE, real_images, fake_images)

        disc_loss = disc_cost + gp * GP_WEIGHT

    disc_gradient = tape.gradient(disc_loss, discriminator.trainable_variables)
    discriminator_optimizer.apply_gradients(zip(disc_gradient, discriminator.trainable_variables))

    return disc_loss

# Notice the use of `tf.function`
# This annotation causes the function to be "compiled".
@tf.function
def train_step_gen():

    noise = random_generator.normal([BATCH_SIZE, noise_dim])
    with tf.GradientTape() as tape:
        # Generate fake images using the generator
        generated_images = generator(noise, training=True)
        # Get the discriminator logits for fake images
        gen_img_logits = discriminator(generated_images, training=True)
        # Calculate the generator loss
        gen_loss = generator_loss(gen_img_logits)

    gen_gradient = tape.gradient(gen_loss, generator.trainable_variables)
    generator_optimizer.apply_gradients(zip(gen_gradient, generator.trainable_variables))

    return gen_loss


numpy_base_dataset = np.load(DATASET_PATH)

def generate_boards():
    generation_noise = random_generator.normal([num_examples_to_generate, noise_dim])
    output = generator(generation_noise)

    decision = discriminator(output)
    deicsion = decision.numpy()

    numpy_output = output.numpy()

    global valid

    room_list = []
    valid_rooms = 0

    for i in range(numpy_output.shape[0]):
        room = np.expand_dims(numpy_output[i], 0)
        room = transform_from_one_hot(room)
        room_list.append(room)
        if valid_room(room):
            valid_rooms += 1
            if in_dataset(numpy_base_dataset, room) == False:
                np.save("generated_images/valid_unique_room" + str(valid), room)
                valid += 1

    return str(f"{len(get_unique(room_list)) / float(num_examples_to_generate):.0%}") + " valid rooms generated:" + str(valid_rooms) + " avg desc score:" + str(np.mean(decision)) 

def train(dataset, epochs):
    start = time.time()
    for epoch in range(epochs):
        i = 0
        for image_batch in dataset:
            disc_loss = train_step_disc(image_batch)

            if i % D_STEPS == 0:
                gen_loss = train_step_gen()

            i += 1

        if (epoch + 1) % 10 == 0:
            print ("gen_loss:", gen_loss.numpy(), "disc_loss", disc_loss.numpy(), "unique rooms generated:", generate_boards(), 'Epoch {} took {} sec'.format(epoch + 1, time.time()-start))
            #generate_boards()
            checkpoint.save(file_prefix = checkpoint_prefix)
            start = time.time()

numpy_dataset = load_dataset_as_one_hot(DATASET_PATH)

print("Found", numpy_dataset.shape[0], "images in dataset")

data_tensor = tf.convert_to_tensor(numpy_dataset, dtype=tf.float32)
dataset = tf.data.Dataset.from_tensor_slices(data_tensor)

train(dataset, EPOCHS)