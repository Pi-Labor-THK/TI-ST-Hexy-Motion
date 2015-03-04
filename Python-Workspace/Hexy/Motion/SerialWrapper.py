'''
Created on 16.02.2015

@author: nwiersch
'''
import serial
from Motion.Speed import Speed
from Motion.Servo import Servo
class SerialWrapper(object):
    '''
    classdocs
    '''
    asyncStarted = False
    
    def __init__(self, Port):
        
        if isinstance(Port, int):
            Port = Port-1
        elif Port is None:
            Port = 0
            
        self.ser = serial.Serial(Port)
        
    def CloseSerial(self):
        """Close Serial Connection"""
        self.ser.close()
        
    def GetDistance(self,Degree=90):
        """Get Distance at a certain degree
        
        Arguments
        Name    Default    Min    Max    Comment
        ----------------------------------------
        Degree  90         0      180
        
        90°  Is the default value, the sensor is directed to the front.
        0°   Corresponds to right
        180° Corresponds to left
        
        Please note, that negative values are unsupported
        """
        if Degree < 0 or Degree > 180:
            raise ValueError("Degree is a value between 0 and 180.")
        
        command = bytes(("0,{0},0,0".format(Degree)),encoding = "ascii")
        self.ser.write(command)
              
        output = str(self.ser.read(3),'ascii')
        if (output[0] == '0'):
            return output.split(',')[1]
        else:
            raise Exception("Could not read correct value: {0}".format(output))
    
    def Move(self,Angle = 90, _Speed = Speed.Undefined, Distance = 0):
        """Move Synchronously
        
        Arguments
        Name        Default    Min    Max    Comment
        --------------------------------------------------
        Angle       90         0      359
        _Speed      Undefined                T:Speed
        Distance    0          1      max    in cm
        
        Angle definition:
        90°  Is the default value (front)
        0°   Corresponds to right
        180° Corresponds to left
        270° Corresponds to back
        
        Please note, that negative values are unsupported
        
        """
        
        if not isinstance(_Speed, Speed):
            raise ValueError("_Speed must be instance of Speed")

        if Angle < 0 or Angle > 359:
            raise ValueError("Angle is a value between 0 and 359.")
        
        if _Speed is Speed.Undefined:
            raise ValueError("_Speed cannot be undefined.")
        
        if Distance < 1:
            raise ValueError("Distance has to be greater than 1.")

        command = bytes(("1,{0},{1},{2}".format(Angle,_Speed,Distance)),encoding = "ascii")
        self.ser.write(command)
              
        output = str(self.ser.read(3),'ascii')
        if (output[0] == '1'):
            return
        else:
            raise Exception("Could not read correct value: {0}".format(output))


    def BeginMove(self,Angle = 90, _Speed = Speed.Undefined): 
        """Move Asynchronously
        
        Arguments
        Name        Default    Min    Max    Comment
        --------------------------------------------------
        Angle       90         0      359
        _Speed      Undefined                T:Speed
        
        Angle definition:
        90°  Is the default value (front)
        0°   Corresponds to right
        180° Corresponds to left
        270° Corresponds to back
        
        Please note, that negative values are unsupported
        """
        if not isinstance(_Speed, Speed):
            raise ValueError("_Speed must be instance of Speed")
        
        if Angle < 0 or Angle > 359:
            raise ValueError("Angle is a value between 0 and 359.")
        
        if _Speed is Speed.Undefined:
            raise ValueError("_Speed cannot be undefined.")
        
        self.asyncStarted = True
        command = bytes(("2,{0},{1},0".format(Angle,_Speed)),encoding = "ascii")
        self.ser.write(command)
              
        output = str(self.ser.read(3),'ascii')
        if (output[0] == '2'):
            return
        else:
            raise Exception("Could not read correct value: {0}".format(output))
        
    def ChangeMove(self,Angle = 90, _Speed = Speed.Undefined):
        if not isinstance(_Speed, Speed):
            raise ValueError("_Speed must be instance of Speed")
        
        if Angle < 0 or Angle > 359:
            raise ValueError("Angle is a value between 0 and 359.")
        
        if _Speed is Speed.Undefined:
            raise ValueError("_Speed cannot be undefined.")
        
        if not self.asyncStarted:
            return self.BeginMove(Angle, _Speed)
        
        command = bytes(("7,{0},{1},0".format(Angle,_Speed)),encoding = "ascii")
        self.ser.write(command)
              
        output = str(self.ser.read(3),'ascii')
        if (output[0] == '2'):
            return
        else:
            raise Exception("Could not read correct value: {0}".format(output))
    
    def EndMove(self):
        """End Asynchronous move"""
        self.asyncStarted = False
        command = bytes("3,0,0,0",encoding = "ascii")
        self.ser.write(command)
              
        output = str(self.ser.read(3),'ascii')
        if (output[0] == '3'):
            return output.split(',')[1]
        else:
            raise Exception("Could not read correct value: {0}".format(output))
    def StandUp(self):
        """Let Stand Up"""
        command = bytes("4,0,0,0",encoding = "ascii")
        self.ser.write(command)
              
        output = str(self.ser.read(3),'ascii')
        if (output[0] == '4'):
            return output.split(',')[1]
        else:
            raise Exception("Could not read correct value: {0}".format(output))
    def LayDown(self):
        """Let Lay Down"""
        command = bytes("5,0,0,0",encoding = "ascii")
        self.ser.write(command)
              
        output = str(self.ser.read(3),'ascii')
        if (output[0] == '5'):
            return output.split(',')[1]
        else:
            raise Exception("Could not read correct value: {0}".format(output))
        
    def MoveServo(self,_Servo = Servo.Undefined,Value = 0):
        """Address Servo directly
        
        Arguments
        Name        Default    Min    Max    Comment
        --------------------------------------------------
        _Servo                               T:Servo
        Value       0          0      180
        """

        if not isinstance(_Servo, Servo):
            raise ValueError("_Servo must be instance of Servo")

        if Value < 0 or Value > 180:
            raise ValueError("Value is a value between 0 and 180.")
        
        if _Servo is Servo.Undefined:
            raise ValueError("_Servo cannot be undefined.")
        
        command = bytes(("6,{0},{1},0".format(_Servo,Value)),encoding = "ascii")
        self.ser.write(command)
              
        output = str(self.ser.read(3),'ascii')
        if (output[0] == '6'):
            return
        else:
            raise Exception("Could not read correct value: {0}".format(output))