from setuptools import find_packages, setup
from glob import glob
import os

package_name = 'roverarm'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        (os.path.join('share', package_name,'launch'), glob('launch/*')),
        (os.path.join('share', package_name,'urdf'), glob('urdf/*')),
        (os.path.join('share', package_name,'config'), glob('config/*')),
        (os.path.join('share', package_name,'meshes'), glob('meshes/*')),
        (os.path.join('share', package_name,'rviz'), glob('rviz/*')),
        (os.path.join('share', package_name,'script'), glob('script/*')),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='pawan',
    maintainer_email='pawan@todo.todo',
    description='TODO: Package description',
    license='Apache-2.0',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
        ],
    },
)