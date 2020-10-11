import numpy as np
import cv2 as cv
import matplotlib.pyplot as plt
import cv2 

cap0 = cv2.VideoCapture(0)




#img1 = cv.imread('box.png',cv.IMREAD_GRAYSCALE)          # queryImage
#img2 = cv.imread('box_in_scene.png',cv.IMREAD_GRAYSCALE) # trainImage



sift = cv.xfeatures2d.SIFT_create()

ret, img2 = cap0.read()

while(True):

    ret, img1 = cap0.read()
   



    # find the keypoints and descriptors with SIFT
    kp1, des1 = sift.detectAndCompute(img1,None)
    kp2, des2 = sift.detectAndCompute(img2,None)



    # FLANN parameters
    FLANN_INDEX_KDTREE = 1
    index_params = dict(algorithm = FLANN_INDEX_KDTREE, trees = 5)
    search_params = dict(checks=50)   # or pass empty dictionary
    flann = cv.FlannBasedMatcher(index_params,search_params)
    matches = flann.knnMatch(des1,des2,k=2)
    # Need to draw only good matches, so create a mask
    matchesMask = [[0,0] for i in range(len(matches))]
    # ratio test as per Lowe's paper

    for i,(m,n) in enumerate(matches):
        if m.distance < 0.9*n.distance:
            matchesMask[i]=[1,0]
            pt1 = kp1[m.queryIdx].pt
            pt2 = kp2[m.trainIdx].pt
            #print(i, pt1,pt2 )
           # print( i, int(pt1[0]),int(pt1[1]) )
            #cv2.circle(img1, (int(pt1[0]),int(pt1[1])), 5, (255,0,255), -1)
            cv2.circle(img2, (int(pt2[0]),int(pt2[1])), 5, (0,0,255), -1)
            cv2.line(img1, (int(pt1[0]), int(pt1[1]*10)), (int(pt1[0]), 600), (0, 255, 0), 3)
            cv2.line(img1, (int(pt2[0]), int(pt2[1]*10)), (int(pt2[0]), 600), (0,0,255), 3)
 
    #draw_params = dict(matchColor = (0,255,0),
                   #    singlePointColor = (255,0,0),
                   #    matchesMask = matchesMask,
                    #   flags = cv.DrawMatchesFlags_DEFAULT)
    #img3 = cv.drawMatchesKnn(img1,kp1,img2,kp2,matches,None,**draw_params)


    imagem = np.concatenate((img1,img2), axis=1)
    
    #cv2.imshow('0',img3)
    cv2.imshow('0',imagem)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
