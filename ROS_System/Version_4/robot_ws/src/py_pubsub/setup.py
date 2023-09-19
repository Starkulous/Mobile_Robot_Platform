from setuptools import setup

package_name = 'py_pubsub'

setup(
    name=package_name,
    version='0.0.0',
    packages=[package_name],
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        ('share/' + package_name, ['launch/robot_launch.py']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='Joe',
    maintainer_email='joechance2002@hotmail.co.uk',
    description='ROS Control System for Capstone Robot<',
    license='Apache License 2.0',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'controller = py_pubsub.joystick:main',
            'robot = py_pubsub.controller:main',
        ],
    },
)
