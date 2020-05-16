

class vector3d(object):
    def __init__(self, x, y, z):
        self.x = x
        self.y = y
        self.z = z
        self.arr = [x,y,z]

    def __abs__(self):
        a = self.arr
        return (a[0]**2 + a[1]**2 + a[2]**2)**0.5

    def __add__(self, other):
        if (isinstance(other, vector3d)):
            newx = self.x + other.x
            newy = self.y + other.y
            newz = self.z + other.z
            return vector3d(newx, newy, newz)
        if (isinstance(other, int) or isinstance(other, float)):
            newx = self.x + other
            newy = self.y + other
            newz = self.z + other
            return vector3d(newx, newy, newz)
        else:
            raise ValueError("Must add vector or int")
    
    def __neg__(self):
        return vector3d(-self.x, -self.y, -self.z)

    def __sub__(self, other):
        return  vector3d.__add__(self, -other)
    
    def __truediv__(self, other):
        if (isinstance(other, int) or isinstance(other, float)):
            return vector3d(self.x/other, self.y/other, self.z/other)
        else:
            raise ValueError("Must divide by number")

    def __repr__(self):
        return "<%i,%i,%i>"%(self.x,self.y,self.z)
    

    def cross(self, other):
        if (isinstance(other,vector3d)):
            i = self.y*other.z - self.z*other.y
            j = self.z*other.x - self.x*other.z
            k = self.x*other.y - self.y*other.x
            return vector3d(i,j,k)
        else:
            raise ValueError("Must cross with vector")

    def dot(self, other):
        if (isinstance(other, vector3d)):
            s = 0
            for i in range(2):
                s += self.arr[i] * other.arr[i]

            return s
