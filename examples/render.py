#!/usr/bin/env python3
# Automatically render screenshots for the given meshes using pymeshlab and polyscope
# Save the camera view, so that all subsequent screenshots use the same camera view
import argparse
import pymeshlab as ml
import polyscope as ps
import json
import os
import sys

def render(filename, choose_scene=False):
    basename = filename[:filename.find('.')]

    ps.init()

    # Do not use these functions, they break the good scaling and centering
    # already applied by default!
    #ps.set_autocenter_structures(True)
    #ps.set_autoscale_structures(True)

    ps.set_up_dir("neg_y_up")
    ps.set_front_dir("neg_y_front")
    ps.set_ground_plane_mode("shadow_only")
    ps.set_ground_plane_height_factor(0) # adjust the plane height
    ps.set_screenshot_extension(".jpg")

    ms = ml.MeshSet()
    ms.load_new_mesh(filename)
    m = ms.mesh(0)
    vertices = m.vertex_matrix()
    faces = m.face_matrix()
    ps_mesh = ps.register_surface_mesh("mesh", vertices, faces, enabled=True, edge_color=[0, 0, 0])
    ps_mesh.set_edge_width(1)
    ps_mesh.set_color([0.8, 0.8, 0.8])  # Set a default gray color
    ps.reset_camera_to_home_view()

    # Look for camera parameters JSON and use it, if it is available and not to be ignored;
    # Otherwise, open GUI so that the user could choose the best camera view
    camera_json = f'{basename}.json'
    if not os.path.isfile(camera_json) or choose_scene:
        print("Please choose the camera view in the opened window and close it once finished")

        # View the point cloud and mesh we just registered in the 3D UI
        ps.show()

        camera = json.loads(ps.get_view_as_json())

        # Save camera parameters string into JSON
        with open(camera_json, 'w') as json_file:
            json.dump(camera, json_file, sort_keys=True, indent=4)

    # Load the camera parameters
    with open(camera_json) as json_file:
        camera = json_file.read()

    # Set the viewport view to those parameters
    ps.set_view_from_json(camera)

    ps.screenshot(f'{filename}_screenshot.jpg')
    ps.remove_all_structures()
    ms.clear()

def main():
    parser = argparse.ArgumentParser(description='Automatically render screenshots for the given meshes using pymeshlab and polyscope. Save the camera view, so that all subsequent screenshots use the same camera view.')
    parser.add_argument('filename', type=str, help='The filename of the mesh to render.')
    parser.add_argument('--choose-scene', action='store_true', help='Enforce choosing the scene and overwrite the JSON with cached scene.')
    args = parser.parse_args()

    render(args.filename, args.choose_scene)

if __name__ == "__main__":
    main()
