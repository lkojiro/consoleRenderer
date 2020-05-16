from vector3d import vector3d

class triangle(object):
    def __init__(self, p0, p1, p2):
        self.p0 = p0
        self.p1 = p1
        self.p2 = p2
        self.e0 = p1-p0
        self.e1 = p2-p1
        self.e2 = p0-p2

    def isInside(self, point):
        A = vector3d.cross(self.e0, point-self.p0)
        B = vector3d.cross(self.e1, point-self.p1)
        C = vector3d.cross(self.e2, point-self.p2)
        return (A.z>=0 and B.z>=0 and C.z>=0)

    #fill in contained points to the buffer with
    #the fill character
    def draw(self, buf, fill):
        #bounding box traversal
        minX = min(self.p0.x, self.p1.x, self.p2.x)
        maxX = max(self.p0.x, self.p1.x, self.p2.x)
        minY = min(self.p0.y, self.p1.y, self.p2.y)
        maxY = max(self.p0.y, self.p1.y, self.p2.y)

        for x in range(minX, maxX):
            for y in range(minY, maxY):
                if (self.isInside(vector3d(x, y, 0))):
                    buf[y][x] = fill
        

