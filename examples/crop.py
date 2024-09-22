#!/usr/bin/env python3
import matplotlib.pyplot as plt
from PIL import Image
import numpy as np
import sys
import json
import glob

if (len(sys.argv) == 2):
    # Load image
    img = Image.open(sys.argv[1])
    plt.imshow(np.array(img))

    # Define cropping area
    crop_area = plt.ginput(2)
    print("Cropping coordinates: ", crop_area)

    # Crop image
    left, upper = map(int, crop_area[0])
    right, lower = map(int, crop_area[1])
    cropped_img = img.crop((left, upper, right, lower))

    # Display cropped image
    plt.imshow(np.array(cropped_img))
    plt.show()
else:
    # Load JSON data
    with open('crop.json', 'r') as f:
        data = json.load(f)

    # For each key in the JSON data
    for key in data:
        # Find all jpg images with the key as basename
        for filename in glob.glob(f'{key}*.jpg'):
            # Open the image
            with Image.open(filename) as img:
                # Crop the image
                cropped_img = img.crop((data[key]['x1'], data[key]['y1'], data[key]['x2'], data[key]['y2']))
                # Save the cropped image
                cropped_img.save(filename)
