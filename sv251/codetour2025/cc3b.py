from math import sqrt

def main():
    images = []
    number_of_image, number_of_vector_per_image, number_of_query = input().split()
    number_of_image = int(number_of_image)
    number_of_vector_per_image = int(number_of_vector_per_image)
    number_of_query = int(number_of_query)
    
    for i in range(number_of_image):
        images.append(input_image(input()))
    
    for i in range(number_of_query):
        # Handle one query
        image_of_query = []
        query = input().split()
        type_of_query = int(query[0])
        param_of_query = int(query[1])
        for i in range(2, len(query)):
            image_of_query.append(int(query[i]))
        
        if type_of_query == 1:
            # Find param image closest to image_of_query
            distances = dict()
            for i in range(len(images)):
                distances[i] = calculate_distance(image_of_query, images[i])
            distances = dict(sorted(distances.items(), key=lambda item:item[1]))
            list_of_ans = list(distances.keys())[:param_of_query:]
            for ans in sorted(list_of_ans):
                print(ans, end=" ")
            
        elif type_of_query == 2:
            # Find all images that has distance with image_of_query less than param
            # Calculate images distances from image_of_query, key is order in database, value is distance
            distances = dict()
            for i in range(len(images)):
                distances[i] = calculate_distance(image_of_query, images[i])
            keys = []
            for key, value in distances.items():
                if value <= param_of_query:  keys.append(key)
            for ans in sorted(keys):
                print(ans, end=" ")
        
        print()
        
        pass
    
    return

def input_image(s: str) -> list:
    image = []
    for number in s.split():
        image.append(int(number))
    return image

def calculate_distance(v1: list, v2: list) -> int:
    d = 0
    for i in range(len(v1)):
        d += (v1[i]-v2[i])*(v1[i]-v2[i])
    return sqrt(d)

main()