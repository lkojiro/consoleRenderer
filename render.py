import sys
import os
import time
import random
import copy

from vector3d import vector3d
from triangle import triangle

screenW = 80
screenH = 40

#clear screen and print buffer to screen
def writeScreen(buf):
    os.system('clear')
    s = ''
    for row in buf:
        for c in row:
            s += c
    #print(s)
    sys.stdout.write(s)


#return empty screen buffer
def blankBuf():
    row = [" " for i in range(screenW)]
    row.append("\n")
    return [copy.deepcopy(row) for i in range(screenH)]

#write character to location (x,y) in buffer
#returns new buffer
def writePixel(buf, ch, x, y):
    assert(x >= 0)
    assert(x < screenW - 1)
    assert(y >= 0)
    assert(y < screenH - 1)
    newBuf = buf
    newBuf[y][x] = ch
    return newBuf

#returns set of points forming a triangle in the screen
def randomTriangle():
    p1 = (random.randint(0, screenW - 2), random.randint(0, screenH - 2))
    p2 = (random.randint(0, screenW - 2), random.randint(0, screenH - 2))
    p3 = (random.randint(0, screenW - 2), random.randint(0, screenH - 2))
    
    v1 = vector3d(p1[0], p1[1], 0)
    v2 = vector3d(p2[0], p2[1], 0)
    v3 = vector3d(p3[0], p3[1], 0)
    
    #make sure triangle points go ccw
    if (vector3d.cross(v2-v1,v3-v1).z < 0):
        return triangle(v1, v3, v2)
    return triangle(v1, v2, v3)

def main():
    buf = blankBuf()
    while(True):
        for i in range(10):
            tri1 = randomTriangle()
            tri1.draw(buf, str(i))
        writeScreen(buf)
        #time.sleep(0.5)
        buf = blankBuf()

if __name__ == '__main__':
    os.system('clear')
    main()

