import cv2
from cv2 import destroyAllWindows
import mediapipe as mp
import numpy as np
import argparse
import sys

def rescale_frame(frame, percent=50):
    width = int(frame.shape[1] * percent/ 100)
    height = int(frame.shape[0] * percent/ 100)
    dim = (width, height)
    return cv2.resize(frame, dim, interpolation =cv2.INTER_AREA)

def main() -> list:
    mp_drawing = mp.solutions.drawing_utils
    mp_drawing_styles = mp.solutions.drawing_styles
    mp_pose = mp.solutions.pose
    parser = argparse.ArgumentParser()
    parser.add_argument("-f", "--file", type=str)

    args = parser.parse_args()
    file = args.file
    cap = cv2.VideoCapture(file)



    # Curl counter variables
    counter = 0 
    min_ang = 0
    max_ang = 0
    min_ang_hip = 0
    max_ang_hip = 0
    stage = None

    width = int(cap.get(cv2.CAP_PROP_FRAME_WIDTH) + 0.5)
    height = int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT) + 0.5)
    
    hip_coor = [] 
    i = 0

    with mp_pose.Pose(min_detection_confidence=0.5, min_tracking_confidence=0.5) as pose:
        while cap.isOpened():
            ret, frame = cap.read()
            if frame is not None:
                frame_ = rescale_frame(frame, percent=100)
            else:
                break
                
            # Recolor image to RGB
            image = cv2.cvtColor(frame_, cv2.COLOR_BGR2RGB)
            image.flags.writeable = False
        
            # Make detection
            results = pose.process(image)
        
            # Recolor back to BGR
            image.flags.writeable = True
            image = cv2.cvtColor(image, cv2.COLOR_RGB2BGR)
            # Extract landmarks
            try:
                landmarks = results.pose_landmarks.landmark    
                # Get coordinates
                hip = [landmarks[mp_pose.PoseLandmark.RIGHT_HIP.value].x,landmarks[mp_pose.PoseLandmark.RIGHT_HIP.value].y]
                hip_coor.append(hip[0])
            except:
                hip_coor.append(-1)
                pass
            # Render detections
            mp_drawing.draw_landmarks(image, results.pose_landmarks, mp_pose.POSE_CONNECTIONS,
                                    mp_drawing.DrawingSpec(color=(0,0,0), thickness=2, circle_radius=2), 
                                    mp_drawing.DrawingSpec(color=(203,17,17), thickness=2, circle_radius=2) 
                                    )     
            cv2.imshow('Mediapipe Feed', image)
            if cv2.waitKey(1) & 0xFF == ord('q'):
                cap.release()
                cv2.destroyAllWindows()
                break
        cap.release()
        cv2.destroyAllWindows()
        f = open("output.txt", "w")
        for i in hip_coor:
            f.write(str(i) + ',')
        return 0
        

if __name__ == '__main__':
    res = main()
    sys.exit(res)
    