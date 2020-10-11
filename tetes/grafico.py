import numpy as np
import time
import matplotlib.pyplot as plt
# grafico





import cv2 as cv
import cv2
from matplotlib import pyplot as plt

cap0 = cv2.VideoCapture(0)
cap1 = cv2.VideoCapture(1)

from matplotlib import pyplot as plt
fast = cv.FastFeatureDetector_create()




while(True):


    
    ret, frame0 = cap0.read()
    ret, frame1 = cap1.read()

    kp0 = fast.detect(frame0,None)
    kp1 = fast.detect(frame1,None)


    img0 = cv.drawKeypoints(frame0, kp1, None, color=(0,255,0))
    #img0 = cv.drawKeypoints(frame0, kp0, None, color=(255,0,0))
    img1 = cv.drawKeypoints(frame1, kp1, None, color=(255,0,0))

    cv2.putText(img0, format(len(kp0)), (50,50), cv2.FONT_HERSHEY_SIMPLEX, 1, (150,255,0),2)
    cv2.putText(img1, format(len(kp1)), (50,50), cv2.FONT_HERSHEY_SIMPLEX, 1, (150,255,0),2)

    
    imagem = np.concatenate((img0,img1), axis=1)

    #print( "Total Keypoints with nonmaxSuppression: {}".format(len(kp0)) )
    
    cv2.imshow('0',imagem)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break


    #grafico
    #plt.plot([1, 2, 3, 4])
    #plt.ylabel('some numbers')
    #plt.show()
    

cap.release()
cv2.destroyAllWindows()



