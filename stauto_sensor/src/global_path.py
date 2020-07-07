#! /usr/bin/env python

import rospy
import tf
import numpy as np
import rospkg
from sensor_msgs.msg import NavSatFix
from geometry_msgs.msg import PoseStamped
from nav_msgs.msg import Path
<<<<<<< HEAD
=======
import tf2_ros
from pyproj import Proj
from pyproj import transform
from geometry_msgs.msg import TransformStamped
>>>>>>> 4df8255a3ba73fe0b4229ed2088380829a1a5507
#from tf.transformations import euler_from_quaternion, quaternion_from_euler

from gps_common import *
import copy
from math import *

<<<<<<< HEAD
=======
WGS84 = { 'proj':'latlong', 'datum':'WGS84', 'ellps':'WGS84', }
GRS80 = { 'proj':'tmerc', 'lat_0':'38', 'lon_0':'127', 'k':1, 'x_0':0,
    'y_0':0, 'ellps':'GRS80', 'units':'m' }
#'lat_0':'38.000036', 'lon_0':'127.00038'
def grs80_to_wgs84(x, y):
   return transform( Proj(**GRS80), Proj(**WGS84), x, y )

def wgs84_to_grs80(x, y):
   return transform( Proj(**WGS84), Proj(**GRS80), y, x )
'''
def pub_tf_transform(lat,lon):
    br = tf2_ros.TransformBroadcaster()

    t = TransformStamped()  # pose of turntable_frame w.r.t. turntable_base
    t.header.stamp = rospy.Time.now()
    t.header.frame_id = 'world'
    t.child_frame_id  = 'GPS_link'
    t.transform.translation.x = lat
    t.transform.translation.y = lon
    t.transform.translation.z = 0
    t.transform.rotation.x = 0
    t.transform.rotation.y = 0
    t.transform.rotation.z = 0
    t.transform.rotation.w = 1

    br.sendTransform(t)
'''
>>>>>>> 4df8255a3ba73fe0b4229ed2088380829a1a5507
def gps_callback(data):
    global lat, lon, utm_lat_lon

    #print(odom_x)
    lat = data.latitude
    lon = data.longitude
<<<<<<< HEAD

    utm_lat_lon = convert_degree_to_meter(lat, lon)

def convert_degree_to_meter(lat,lon):

    alpha = lat*pi/180
    beta = lon*pi/180

    a = 6377397.155
    f = 1/299.1528128
    b = a*(1-f)
    k = 1
    x_plus = 500000
    y_plus = 200000

    e1 = (a**2-b**2)/a**2
    e2 = (a**2-b**2)/b**2
    alpha0 = 38 *pi/180
    beta0 = (125+0.002890277)*pi/180

    T = pow(tan(alpha),2)
    C = e1/(1-e1)*pow(cos(alpha),2)
    AA = (beta-beta0)*cos(alpha)  #both radian

    N = a/sqrt( 1-e1*sin(alpha)**2 )
    M = a*(alpha*(1-e1/4-3*e1**2/64-5*e1**3/256)-sin(2*alpha)*(3*e1/8+3*e1**2/32+45*e1**3/1024)
        +sin(4*alpha)*(15*e1**2/256+45*e1**3/1024)-35*e1**3*sin(6*alpha)/3072)

    M0 = a*(alpha0*(1-e1/4-3*e1**2/64-5*e1**3/256)-sin(2*alpha0)*(3*e1/8+3*e1**2/32+45*e1**3/1024)
         +sin(4*alpha0)*(15*e1**2/256+45*e1**3/1024)-35*e1**3*sin(6*alpha0)/3072)

    Y = y_plus + k*N*(AA+AA**3*(1-T+C)/6+pow(AA,5)*(5-18*T+T*T+72*C-58*e2)/120)
    X = x_plus + k*(M-M0+N*tan(alpha)*(AA*AA/2 + pow(AA,4)*(5-T+9*C+4*C*C)/24 +
        pow(AA,6)*(61-58*T+T*T+600*C-330*e2)/720))

    return [X,Y]


def find_gps_step():
    global last_step
    min_length=100
    cur_step=0
=======
    #print(lat, lon)
    utm_lat_lon = wgs84_to_grs80(lat, lon)

def find_gps_step(last_step, cur_gps):
    min_length=100
    cur_step=0

>>>>>>> 4df8255a3ba73fe0b4229ed2088380829a1a5507
    for step_gps in range(last_step-4):
        gps_n = gps_data[step_gps].split(',')
        gps_n_1 = gps_data[step_gps+1].split(',')
        gps_n_2 = gps_data[step_gps+2].split(',')


        # gps_n = [float(gps_n[0]) - float(gps_origin[0]), float(gps_n[1]) - float(gps_origin[1])]
        # gps_n_1 = [float(gps_n_1[0]) - float(gps_origin[0]), float(gps_n_1[1])- float(gps_origin[1])]
        gps_n = [float(gps_n[0]), float(gps_n[1])]
        gps_n_1 = [float(gps_n_1[0]), float(gps_n_1[1])]
        gps_n_2 = [float(gps_n_2[0]), float(gps_n_2[1])]


<<<<<<< HEAD
        utm_gps_n = convert_degree_to_meter(gps_n[0],gps_n[1])
        utm_gps_n_1 = convert_degree_to_meter(gps_n_1[0],gps_n_1[1])
        utm_gps_n_2 = convert_degree_to_meter(gps_n_2[0],gps_n_2[1])
        utm_gps_cur = convert_degree_to_meter(lat,lon)
=======
        utm_gps_n = wgs84_to_grs80(gps_n[0],gps_n[1])
        utm_gps_n_1 = wgs84_to_grs80(gps_n_1[0],gps_n_1[1])
        utm_gps_n_2 = wgs84_to_grs80(gps_n_2[0],gps_n_2[1])
        utm_gps_cur = wgs84_to_grs80(lat,lon)
>>>>>>> 4df8255a3ba73fe0b4229ed2088380829a1a5507

        length1 = sqrt((utm_gps_cur[0]-utm_gps_n[0])**(2)+(utm_gps_cur[1]-utm_gps_n[1])**(2))
        length2 = sqrt((utm_gps_cur[0]-utm_gps_n_1[0])**(2)+(utm_gps_cur[1]-utm_gps_n_1[1])**(2))

        length = length1+length2
        '''
        line_data_x=[utm_gps_n[0],utm_gps_n_1[0],utm_gps_n_2[0]]
        line_data_y=[utm_gps_n[1],utm_gps_n_1[1],utm_gps_n_2[1]]

        fp1 = np.polyfit(line_data_x,line_data_y,1)


        y= fp1[0]*step_gps+fp1[1]

        length=abs(fp1[0]*utm_gps_cur[0] - utm_gps_cur[1] + fp1[1])/sqrt(fp1[0]**(2)+(-1)**(2)) #find length
        '''

<<<<<<< HEAD
        if(length<min_length):
=======
        if(length<min_length and cur_gps==0):
            min_length=length
            cur_step=step_gps+1

        elif (length<min_length and cur_gps-2 <= step_gps <= cur_gps+2):
>>>>>>> 4df8255a3ba73fe0b4229ed2088380829a1a5507
            min_length=length
            cur_step=step_gps+1

    return cur_step

def path_converter(gps, step_gps, last_step):
    #print(step_gps)
    pathmsg.header.seq = step_gps
    pathmsg.header.stamp = rospy.Time.now()
<<<<<<< HEAD
    pathmsg.header.frame_id = "base_link"
=======
    pathmsg.header.frame_id = "map"
>>>>>>> 4df8255a3ba73fe0b4229ed2088380829a1a5507

    pose = PoseStamped()
    pose.header.seq = step_gps
    pose.header.stamp = rospy.Time.now()
<<<<<<< HEAD
    pose.header.frame_id = "base_link"

    x,y=convert_degree_to_meter(gps[0],gps[1])
    pose.pose.position.x = x
=======
    pose.header.frame_id = "map"

    x,y=wgs84_to_grs80(gps[0],gps[1])
    pose.pose.position.x = x
    print(x)
>>>>>>> 4df8255a3ba73fe0b4229ed2088380829a1a5507
    pose.pose.position.y = y
    pose.pose.position.z = 0

    pose.pose.orientation.x = 0
    pose.pose.orientation.y = 0
    pose.pose.orientation.z = 0
    pose.pose.orientation.w = 0

    #rospy.sleep(0.5)
    pathmsg.poses.append(pose)



    if(step_gps == last_step-1):
        path_pub.publish(pathmsg)
<<<<<<< HEAD
        print("TACHO TUESDAY!!!!!!!!!!!")
=======
        print("global path finish!!!!!!!!!!!")
>>>>>>> 4df8255a3ba73fe0b4229ed2088380829a1a5507

def current_step_pub(step_gps):

    current_pose = PoseStamped()

    current_pose.header.seq = 0
    current_pose.header.stamp = rospy.Time.now()
    current_pose.header.frame_id = "base_link"

    current_pose.pose.position.x = pathmsg.poses[step_gps].pose.position.x
    current_pose.pose.position.y = pathmsg.poses[step_gps].pose.position.y
    current_pose.pose.position.z = step_gps

    current_pose.pose.orientation.x = 0
    current_pose.pose.orientation.y = 0
    current_pose.pose.orientation.z = 0
    current_pose.pose.orientation.w = 0


    step_pub.publish(current_pose)
    print(current_pose)
<<<<<<< HEAD

=======
'''
>>>>>>> 4df8255a3ba73fe0b4229ed2088380829a1a5507
def pub_utm_cur_gps(lat,lon):

    utm_gpsmsg.header.stamp = rospy.Time.now()
    utm_gpsmsg.header.frame_id = "gps_link"
    utm_gpsmsg.latitude=lat
    utm_gpsmsg.longitude=lon
    utm_gpsmsg. position_covariance_type=0
    utm_cur_gps_pub.publish(utm_gpsmsg)
    #print(gpsmsg)
<<<<<<< HEAD

if __name__ == '__main__':

    rospy.init_node('Global_path')
    listener = tf.TransformListener()

    path_pub = rospy.Publisher('global_path', Path, queue_size=10)
=======
'''
if __name__ == '__main__':

    rospy.init_node('Global_path')
    #listener = tf.TransformListener()

    path_pub = rospy.Publisher('global_path', Path, queue_size=10)
    step_pub = rospy.Publisher('current_step', PoseStamped, queue_size=10)
    #utm_cur_gps_pub = rospy.Publisher("/gps/current_robot_position",NavSatFix,queue_size=10)
    rospy.Subscriber("/gps/fix",NavSatFix,gps_callback)
>>>>>>> 4df8255a3ba73fe0b4229ed2088380829a1a5507

    rospack = rospkg.RosPack()
    rospack.list()
    arg_name = rospack.get_path('stauto_sensor') + "/src/gps_data/"

    f = open(arg_name + "gps_data_seoultech.txt","r")

    gps_data = f.readlines()
    last_step=len(gps_data)
    lat = 0
    lon = 0
    utm_lat_lon=[0,0]
    step_gps = 0
    path_pub_sign=True

    pathmsg=Path()
    utm_gpsmsg=NavSatFix()

    rospy.sleep(1)

    init_time=rospy.Time.now()

    while not rospy.is_shutdown():
        if (step_gps<last_step):
            gps_n = gps_data[step_gps].split(',')
            gps_n = [float(gps_n[0]), float(gps_n[1])]
            path_converter(gps_n, step_gps, last_step)
            step_gps=step_gps+1
        else:
            path_pub_sign=False

<<<<<<< HEAD
=======
        if (path_pub_sign==True):
            if (step_gps<last_step):
                #print(step_gps)

                gps_n = gps_data[step_gps].split(',')
                gps_n = [float(gps_n[0]), float(gps_n[1])]

                path_converter(gps_n, step_gps, last_step)
                step_gps=step_gps+1
            else:
                path_pub_sign=False
                step_gps=0
        else:
            step_gps=find_gps_step(last_step, step_gps)

            current_step_pub(step_gps)

            #pub_utm_cur_gps(utm_lat_lon[0], utm_lat_lon[1])
            #pub_tf_transform(lat,lon)

>>>>>>> 4df8255a3ba73fe0b4229ed2088380829a1a5507
    else:
        pass
