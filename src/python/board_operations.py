import numpy as np
import os

from numpy.core.fromnumeric import reshape

SIMILAR_THRESHOLD = 44
DATA_IMAGE_SIZE = (1, 7, 7, 1)

ROOM_SIZE = 7 * 7
NUMBER_OF_TILE_TYPES = 7

EMPTY = 0
ENEMY = 1
TREASURE = 2
WATER = 3
TABLE = 4
DRESSER = 5
MONUMENT = 6

def transform_from_one_hot(one_hot_image):
  normal_image = np.argmax(one_hot_image, axis=-1)
  normal_image = np.expand_dims(normal_image, -1)
  return normal_image

def load_dataset_as_one_hot(path):
    images = np.load(path)

    one_hot_shape = list(images.shape)
    one_hot_shape[-1] = NUMBER_OF_TILE_TYPES
    one_hot_images = np.zeros(shape=one_hot_shape)


    for i in range(images.shape[0]):
      for j in range(images.shape[1]):
        for k in range(images.shape[2]):
          index = images[i, j, k, 0]
          one_hot_images[i, j, k, index] = 1

    # needed because dataset_from_slices reduce first dim
    return np.expand_dims(one_hot_images, 1).astype(np.float32)

def in_dataset(dataset, array):
    for dataset_array in dataset:
        if arrays_similar(dataset_array, array):
            return True

    return False

def load_list_of_arrays_from_folder(folder_path):
    list_of_arrays = []

    files = os.listdir(folder_path)
    for file in files:
        PATH = os.path.join(folder_path, file)
        list_of_arrays.append(np.load(PATH))

    return list_of_arrays

def arrays_similar(first, second):
    return (first == second).sum() > SIMILAR_THRESHOLD

def convert_to_4D_list(dataset):
    list = []
    for i in range(dataset.shape[0]):
        list.append(np.reshape(dataset[i], DATA_IMAGE_SIZE))

    return list

def get_unique(list_of_arrays):
    unique_arrays = []
    for i in range(len(list_of_arrays)):
        is_unique = True    

        for array in unique_arrays:
            if arrays_similar(array, list_of_arrays[i]):
                is_unique = False

        if is_unique:
            unique_arrays.append(list_of_arrays[i])

    return unique_arrays
    
def combine_datasets(first, second):
    return np.concatenate((first, second))

def combine_dataset_lists(first, second):
    new_list = []

    for item in first:
        new_list.append(item)
    for item in second:
        new_list.append(item)

    return new_list

def batched_dataset_from_list(dataset_list):
    batched_dataset = np.reshape(dataset_list[0], DATA_IMAGE_SIZE)

    for i in range(1, len(dataset_list)):
        batched_dataset = np.concatenate((batched_dataset, np.reshape(dataset_list[i], DATA_IMAGE_SIZE)))

    return batched_dataset


# ROOM VALIDATION

def is_on_border(x, y):
    return x == 0 or y == 0 or x == 6 or y == 6

def has_neighbour_moore(room, x, y, TYPE, depth=0):
    if x > 0 and y > 0:
        if room[x - 1][y - 1] == TYPE:
            return True
    if x > 0 and y < room.shape[0] - 1:
        if room[x - 1][y + 1] == TYPE:
            return True
    if x < room.shape[0] - 1 and y > 0:
        if room[x + 1][y - 1] == TYPE:
            return True
    if x < room.shape[0] - 1 and y < room.shape[0] - 1:
        if room[x + 1][y + 1] == TYPE:
            return True

    if has_neighbour_neumann(room, x, y, TYPE, 0):
        return True
    
    if depth > 0:
        if has_neighbour_moore(room, x - 1, y, TYPE, depth - 1):
            return True
        if has_neighbour_moore(room, x + 1, y, TYPE, depth - 1):
            return True
        if has_neighbour_moore(room, x, y - 1, TYPE, depth - 1):
            return True
        if has_neighbour_moore(room, x, y + 1, TYPE, depth - 1):
            return True
        if has_neighbour_moore(room, x - 1, y - 1, TYPE, depth - 1):
            return True
        if has_neighbour_moore(room, x + 1, y - 1, TYPE, depth - 1):
            return True
        if has_neighbour_moore(room, x - 1, y + 1, TYPE, depth - 1):
            return True
        if has_neighbour_moore(room, x + 1, y + 1, TYPE, depth - 1):
            return True

    return False

def has_neighbour_neumann(room, x, y, TYPE, depth=0):
    if x > 0:
        if room[x - 1][y] == TYPE:
            return True
    if y > 0:
        if room[x][y - 1] == TYPE:
            return True
    if x < room.shape[0] - 1:
        if room[x + 1][y] == TYPE:
            return True
    if y < room.shape[1] - 1:
        if room[x][y + 1] == TYPE:
            return True
    
    if depth > 0:
        if x > 0:
            if has_neighbour_neumann(room, x - 1, y, TYPE, depth - 1):
                return True
        if x < room.shape[0] - 1:
            if has_neighbour_neumann(room, x + 1, y, TYPE, depth - 1):
                return True
        if y > 0:
            if has_neighbour_neumann(room, x, y - 1, TYPE, depth - 1):
                return True
        if y < room.shape[0] - 1:
            if has_neighbour_neumann(room, x, y + 1, TYPE, depth - 1):
                return True

    return False

def check_monument_2x2_pattern(room):
    indexes = np.where(room==MONUMENT)

    starting_x = indexes[0][0]
    starting_y = indexes[1][0]

    if (room[starting_x:starting_x+2, starting_y:starting_y+2] == MONUMENT).sum() == 4:
        return True

    return False

def check_monument_not_on_border(room):
    indexes = np.where(room==MONUMENT)
    for i in range(len(indexes[0])):
        if is_on_border(indexes[0][i], indexes[1][i]):
            return False
    return True

def check_monument_neighbours_correctness(room):
    invalid_neighbours = [DRESSER, TABLE]
    indexes = np.where(room==MONUMENT)
    for i in range(len(indexes[0])):
        for invalid_neighbour in invalid_neighbours:
            if has_neighbour_moore(room, indexes[0][i], indexes[1][i], invalid_neighbour):
                return False

    return True

def check_monument_correctness(room):
    if (room == MONUMENT).sum() == 0:
        return True

    if (room == MONUMENT).sum() != 4:
        return False

    if check_monument_not_on_border(room) == False:
        return False
    if check_monument_neighbours_correctness(room) == False:
        return False
    if check_monument_2x2_pattern(room) == False:
        return False

    return True

def check_water_correctness(room):
    if (room == WATER).sum() == 0:
        return True

    if (room == WATER).sum() > 12:
        return False

    indexes = np.where(room==WATER)

    for i in range(len(indexes[0])):
        if has_neighbour_neumann(room, indexes[0][i], indexes[1][i], WATER) == False:
            return False

    return True

def check_treasure_enemy_nearby(room):
    indexes = np.where(room==TREASURE)

    for i in range(len(indexes[0])):
        if has_neighbour_neumann(room, indexes[0][i], indexes[1][i], ENEMY, depth=1) == False:
            return False

def check_treasure_correctness(room):
    if (room == TREASURE).sum == 0:
        return True

    if (room == TREASURE).sum() > 2:
        return False

    if check_treasure_enemy_nearby(room) == False:
        return False

    return True

def check_enemy_correctness(room):
    if (room == ENEMY).sum() > 4:
        return False

    return True

def check_dresser_on_border(room):
    indexes = np.where(room==DRESSER)
    for i in range(len(indexes[0])):
        if is_on_border(indexes[0][i], indexes[1][i]) == False:
            return False

    return True

def check_dresser_corner_condition(room):
    if room[0][0] == DRESSER and room[0][1] == DRESSER and room[1][0] == DRESSER:
        return False
    if room[0][6] == DRESSER and room[0][5] == DRESSER and room[1][6] == DRESSER:
        return False
    if room[6][6] == DRESSER and room[6][5] == DRESSER and room[5][6] == DRESSER:
        return False
    if room[6][0] == DRESSER and room[6][1] == DRESSER and room[5][0] == DRESSER:
        return False

    return True

def check_dresser_has_same_neighbour(room):
    indexes = np.where(room==DRESSER)

    for i in range(len(indexes[0])):
        if has_neighbour_neumann(room, indexes[0][i], indexes[1][i], DRESSER, depth=0) == False:
            return False

    return True

def check_dresser_ensure_even_in_line(room):
    dressers_in_row = 0
    for i in range(room.shape[0]):
        if room[0][i] == DRESSER:
            dressers_in_row += 1
        else:
            if dressers_in_row == 3 or dressers_in_row == 5:
                return False
            else:
                dressers_in_row = 0

    if dressers_in_row == 3 or dressers_in_row == 5:
        return False

    dressers_in_row = 0
    for i in range(room.shape[0]):
        if room[6][i] == DRESSER:
            dressers_in_row += 1
        else:
            if dressers_in_row == 3 or dressers_in_row == 5:
                return False
            else:
                dressers_in_row = 0

    if dressers_in_row == 3 or dressers_in_row == 5:
        return False

    dressers_in_row = 0
    for i in range(room.shape[0]):
        if room[i][0] == DRESSER:
            dressers_in_row += 1
        else:
            if dressers_in_row == 3 or dressers_in_row == 5:
                return False
            else:
                dressers_in_row = 0

    if dressers_in_row == 3 or dressers_in_row == 5:
        return False

    dressers_in_row = 0
    for i in range(room.shape[0]):
        if room[i][6] == DRESSER:
            dressers_in_row += 1
        else:
            if dressers_in_row == 3 or dressers_in_row == 5:
                return False
            else:
                dressers_in_row = 0

    if dressers_in_row == 3 or dressers_in_row == 5:
        return False

    return True

def check_dresser_ensure_1x2_pattern(room):
    if check_dresser_ensure_even_in_line(room) == False:
        return False

    return True

def check_dresser_correctness(room):
    if (room == DRESSER).sum() == 0:
        return True

    if check_dresser_on_border(room) == False:
        return False
    if check_dresser_corner_condition(room) == False:
        return False
    if check_dresser_has_same_neighbour(room) == False:
        return False
    if check_dresser_ensure_1x2_pattern(room) == False:
        return False

    return True

def check_table_2x3_pattern(room):
    indexes = np.where(room==TABLE)

    starting_x = indexes[0][0]
    starting_y = indexes[1][0]

    if (room[starting_x:starting_x+2, starting_y:starting_y+3] == TABLE).sum() == 6:
        return True
    if (room[starting_x:starting_x+3, starting_y:starting_y+2] == TABLE).sum() == 6:
        return True
    
    return False

def check_table_correctness(room):
    if (room == TABLE).sum() == 0:
        return True

    if (room == TABLE).sum() != 6:
        return False 

    if check_table_2x3_pattern(room) == False:
        return False

    return True

def augment_data(array_list):
    augmented_list = []

    for array in array_list:
        arr = np.reshape(array, (7, 7))
        
        rotated_arrays_list = [arr]
        rotated_arrays_list.append(np.rot90(rotated_arrays_list[0]))
        rotated_arrays_list.append(np.rot90(rotated_arrays_list[1]))
        rotated_arrays_list.append(np.rot90(rotated_arrays_list[2]))

        for rotated_array in rotated_arrays_list:
            augmented_list.append(rotated_array)
            augmented_list.append(np.fliplr(rotated_array))
            augmented_list.append(np.flipud(rotated_array))

    return augmented_list

def validate_dataset(array_list):
    if len(array_list) != len(get_unique(array_list)):
        print("Error occured when loading dataset, it does not contain unique arrays!")
        a.e() # tmp throw
    for array in array_list:
        if valid_room(array) == False:
            print("Error occured when loading dataset, it contains invalid array")
            print(np.reshape(array, (7, 7)))

def valid_room(room):
    squeezed_room = np.reshape(room, (7, 7))

    if (room == EMPTY).sum() == ROOM_SIZE:
        return False
    if (room == EMPTY).sum() < 12 or (room == EMPTY).sum() > 33:
        return False
    if check_enemy_correctness(squeezed_room) == False:
        #print("Enemy incorrectness")
        return False
    if check_treasure_correctness(squeezed_room) == False:
        #print("Treasure incorrectness")
        return False
    if check_monument_correctness(squeezed_room) == False:
        #print("Monument incorrectness")
        return False
    if check_water_correctness(squeezed_room) == False:
        #print("Water incorrectness")
        return False
    if check_dresser_correctness(squeezed_room) == False:
        #print("Dresser incorrectness")
        return False
    if check_table_correctness(squeezed_room) == False:
        #print("Table incorrectness")
        return False

    return True