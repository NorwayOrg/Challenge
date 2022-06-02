from __future__ import print_function
import sys
import glob
import cv2 as cv
import numpy as np
use_mask = False
img = None
templ = None
mask = None
image_window = "Source Image"
result_window = "Result window"
match_method = 0
max_Trackbar = 5
def main():
    
    global img
    global templ
    global webcam
    #webcam = cv.VideoCapture('E:\VS_projects\OpenCV\contest\project1.avi')
    webcam = cv.VideoCapture(0)
    #img = cv.imread("E:\VS_projects\OpenCV\contest\img\\00700.jpg", cv.IMREAD_COLOR)
    templ = cv.imread("E:\VS_projects\OpenCV\ded\\template\\ball_temp8.jpg", cv.IMREAD_COLOR)
    match = []

    while True:
        #for filename in glob.glob('E:\VS_projects\OpenCV\ded\\template\\*.jpg'):
            #templ = cv.imread(filename)
            ret, frame = webcam.read()

            mask = cv.TM_CCOEFF
            #if ((img is None) or (templ is None) or (use_mask and (mask is None))):
            #   print('Can\'t read one of the images')
            #    return -1
            
            cv.namedWindow( result_window, cv.WINDOW_AUTOSIZE )
            
            trackbar_label = 'Method: \n 0: SQDIFF \n 1: SQDIFF NORMED \n 2: TM CCORR \n 3: TM CCORR NORMED \n 4: TM COEFF \n 5: TM CCOEFF NORMED'
            #cv.createTrackbar( trackbar_label, image_window, match_method, max_Trackbar, MatchingMethod )
            comp = MatchingMethod(mask,frame)
            match =[comp]

            biggest = max(match)


            cv.imshow(result_window, result)
            cv.imshow('nanoCam',frame)
            cv.moveWindow('nanoCam',0,0) 
            if cv.waitKey(1)==ord('q'):
                break  
def MatchingMethod(param,frame):
    global match_method
    global matchLoc
    match_method = param
    img_display = frame
    global result
    method_accepts_mask = (cv.TM_SQDIFF == match_method or match_method == cv.TM_CCORR_NORMED)
    if (use_mask and method_accepts_mask):
        result = cv.matchTemplate(img_display, templ, match_method, None, mask)
    else:
        result = cv.matchTemplate(img_display, templ, match_method)
    
    
    cv.normalize( result, result, 0, 1, cv.NORM_MINMAX, -1 )
    
    _minVal, _maxVal, minLoc, maxLoc = cv.minMaxLoc(result, None)
    #print(_minVal, _maxVal)
    comp = _minVal
    
    if (match_method == cv.TM_SQDIFF or match_method == cv.TM_SQDIFF_NORMED):
        matchLoc = minLoc
    else:
        matchLoc = maxLoc
    #if(_minVal>=0):
    #print(matchLoc, matchLoc[0] + templ.shape[0])
    #cv.rectangle(frame, matchLoc, (matchLoc[0] + templ.shape[0], matchLoc[1] + templ.shape[1]), (0,0,0), 2, 8, 0 )
    #cv.rectangle(img_display, matchLoc, (matchLoc[0] + templ.shape[0], matchLoc[1] + templ.shape[1]), (0,0,0), 2, 8, 0 )
    cv.rectangle(result, matchLoc, (matchLoc[0] + templ.shape[0], matchLoc[1] + templ.shape[1]), (0,0,0), 2, 8, 0 )
    roi = frame[matchLoc[1]:(matchLoc[1] + templ.shape[1]), matchLoc[0]: (matchLoc[0] + templ.shape[0])].copy()
    roihsv =  cv.cvtColor(roi, cv.COLOR_BGR2HSV)
    white_lower = np.array([0, 0, 233], np.uint8)
    white_upper = np.array([179, 89, 255], np.uint8)
    white_mask = cv.inRange(roihsv, white_lower, white_upper)
    res_white = cv.bitwise_and(roi, roi,
                                mask = white_mask)
    blue_lower = np.array([32, 23, 137], np.uint8)
    blue_upper = np.array([156, 221, 255], np.uint8)
    blue_mask = cv.inRange(roihsv, blue_lower, blue_upper)
    res_blue = cv.bitwise_and(roi, roi,
                                mask = blue_mask)
    yellow_lower = np.array([22, 37, 85], np.uint8)
    yellow_upper = np.array([60, 255, 255], np.uint8)
    yellow_mask = cv.inRange(roihsv, yellow_lower, yellow_upper)
  
    red_lower = np.array([1, 87, 111], np.uint8)
    red_upper = np.array([10, 255, 255], np.uint8)
    red_mask = cv.inRange(roihsv, red_lower, red_upper)
  
    contours_white,_ = cv.findContours(white_mask, cv.RETR_EXTERNAL, cv.CHAIN_APPROX_SIMPLE)#array of arrays of contours( each array is a list of contours that outlines one of the objects of interest, each contour is set of x,y coordinates)
    contours_blue,_ = cv.findContours(blue_mask, cv.RETR_EXTERNAL, cv.CHAIN_APPROX_SIMPLE)
    contours_yellow,_ = cv.findContours(yellow_mask, cv.RETR_EXTERNAL, cv.CHAIN_APPROX_SIMPLE)#array of arrays of contours( each array is a list of contours that outlines one of the objects of interest, each contour is set of x,y coordinates)
    contours_red,_ = cv.findContours(red_mask, cv.RETR_EXTERNAL, cv.CHAIN_APPROX_SIMPLE)#array of arrays of contours( each array is a list of contours that outlines one of the objects of interest, each contour is set of x,y coordinates)
    
    contours = sorted(contours_red,key=lambda x:cv.contourArea(x),reverse=True)#sort to have the biggest ones first, what parameter we sort by, lambda to build in the function right into code
    contours
    for cont in contours:#parameter cont that is gonna step through each contour in the main array contour
        area = cv.contourArea(cont)#area of the individual cont
        if area>=60:
            cv.drawContours(res_white,[cont], 0,(255,0,0),3)#expects a list of cont
            cv.rectangle(frame, matchLoc, (matchLoc[0] + templ.shape[0], matchLoc[1] + templ.shape[1]), (0,0,0), 2, 8, 0 )
    #cv.drawContours(res_white, contours, 0,(255,0,0),3)# -1 all of the contours, 0 first one

    cv.imshow('roi',res_white)
    cv.moveWindow('roi',700,0)

    return comp

if __name__ == "__main__":
    main()
    webcam.release()