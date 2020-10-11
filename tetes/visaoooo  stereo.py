import cv2
import numpy as np
import cv2 as cv
from matplotlib import pyplot as plt




cap0 = cv2.VideoCapture(0)
cap1 = cv2.VideoCapture(1)






while(True):

    ret, frame0 = cap0.read()
    ret, frame1 = cap1.read()

    i0= cv2.cvtColor(frame0, cv2.COLOR_BGR2GRAY)
    i= cv2.cvtColor(frame0, cv2.COLOR_BGR2GRAY)    


    template = i0
    w, h = template.shape[::-1]
    x,y = 0,0

    


    
    res = cv2.matchTemplate(i,template,3)
    min_val, max_val, min_loc, max_loc = cv2.minMaxLoc(res)
    top_left = max_loc
    print(top_left)
    bottom_right = (top_left[0] + w, top_left[1] + h)
    
    x = (top_left[0] + bottom_right[0])/2
    y = (top_left[1] + bottom_right[1])/2




    #Draw Rectangle Match
    cv2.rectangle(frame0, top_left, bottom_right, (0, 255, 0), 3)
    cv2.putText(frame0, "["+ str(x)+","+str(y)+"]", (bottom_right[0]+10,bottom_right[1]+10), cv2.FONT_HERSHEY_SIMPLEX, 1, (255,255,255), 2)




    imagem = np.concatenate((frame0,frame1), axis=1)

    

    cv2.imshow('0',imagem)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break 

cv2.destroyAllWindows()
