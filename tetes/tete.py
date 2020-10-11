
import cv2 as cv
import cv2
from matplotlib import pyplot as plt



import numpy as np
import cv2
from matplotlib import pyplot as plt

cap0 = cv2.VideoCapture(0)
cap1 = cv2.VideoCapture(1)

from matplotlib import pyplot as plt
fast = cv.FastFeatureDetector_create()


while(True):


    
    ret, frame0 = cap0.read()
    ret, frame1 = cap1.read()



    stereo = cv2.StereoBM(cv2.STEREO_BM_BASIC_PRESET,ndisparities=16, SADWindowSize=15)
    disparity = stereo.compute(frame0,frame1)


    cv2.imshow('0',disparity)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
