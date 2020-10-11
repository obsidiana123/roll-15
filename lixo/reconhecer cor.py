import cv2
import numpy

x1 = 637
y1 = 479
centox1  = int(637/2)
centroy1 = int(479/2)

cam = cv2.VideoCapture(0)
kernel = numpy.ones((5 ,5), numpy.uint8)

while (True):
    ret, frame = cam.read()
    rangomax = numpy.array([0, 0, 250]) # B, G, R
    rangomin = numpy.array([0, 0, 50])
    mask = cv2.inRange(frame, rangomin, rangomax)
    # reduce the noise
    opening = cv2.morphologyEx(mask, cv2.MORPH_OPEN, kernel)

    x, y, w, h = cv2.boundingRect(opening)
    #print(int((x+w)/2))
    #print(int((y+h)/2))
    #cv2.rectangle(frame, (x, y), (x+w, y + h), (0, 255, 0), 3)
    
    cv2.circle(frame, (centox1, centroy1), 5, (0, 255, 0), -1)
    cv2.circle(frame, (int(x+w/2), int(y+h/2)), 5, (0, 0, 255), -1)


    (b, g, r) = frame[centox1, centox1]
    rgb = (b, g, r)
    print(rgb)

    

    cv2.imshow('camera', frame)

    k = cv2.waitKey(1) & 0xFF

    if k == 27:
        break
