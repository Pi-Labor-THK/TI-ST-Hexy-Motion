'''
Created on 16.02.2015

@author: nwiersch
'''

from Motion.SerialWrapper import SerialWrapper
from Motion.Directions import Direction
from Motion.Speed import Speed
from Motion.Servo import Servo

SW = SerialWrapper(31)
SW.Move(10, Speed.Fast, Direction.Forward, 10)
print("Getting Distance...")
print(SW.GetDistance(90))
SW.CloseSerial()
