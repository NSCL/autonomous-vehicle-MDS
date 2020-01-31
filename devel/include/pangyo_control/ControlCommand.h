// Generated by gencpp from file pangyo_control/ControlCommand.msg
// DO NOT EDIT!


#ifndef PANGYO_CONTROL_MESSAGE_CONTROLCOMMAND_H
#define PANGYO_CONTROL_MESSAGE_CONTROLCOMMAND_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace pangyo_control
{
template <class ContainerAllocator>
struct ControlCommand_
{
  typedef ControlCommand_<ContainerAllocator> Type;

  ControlCommand_()
    : gear(0)
    , speed(0)
    , steer(0.0)
    , brake(0)  {
    }
  ControlCommand_(const ContainerAllocator& _alloc)
    : gear(0)
    , speed(0)
    , steer(0.0)
    , brake(0)  {
  (void)_alloc;
    }



   typedef uint16_t _gear_type;
  _gear_type gear;

   typedef uint16_t _speed_type;
  _speed_type speed;

   typedef float _steer_type;
  _steer_type steer;

   typedef uint16_t _brake_type;
  _brake_type brake;





  typedef boost::shared_ptr< ::pangyo_control::ControlCommand_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::pangyo_control::ControlCommand_<ContainerAllocator> const> ConstPtr;

}; // struct ControlCommand_

typedef ::pangyo_control::ControlCommand_<std::allocator<void> > ControlCommand;

typedef boost::shared_ptr< ::pangyo_control::ControlCommand > ControlCommandPtr;
typedef boost::shared_ptr< ::pangyo_control::ControlCommand const> ControlCommandConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::pangyo_control::ControlCommand_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::pangyo_control::ControlCommand_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace pangyo_control

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsMessage': True, 'HasHeader': False, 'IsFixedSize': True}
// {'pangyo_control': ['/home/choiys/stauto_ws/src/stauto_sensor/msg'], 'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__dir__', '__doc__', '__eq__', '__format__', '__ge__', '__getattribute__', '__gt__', '__hash__', '__init__', '__le__', '__lt__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsMessage< ::pangyo_control::ControlCommand_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::pangyo_control::ControlCommand_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::pangyo_control::ControlCommand_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::pangyo_control::ControlCommand_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::pangyo_control::ControlCommand_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::pangyo_control::ControlCommand_<ContainerAllocator> const>
  : TrueType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::pangyo_control::ControlCommand_<ContainerAllocator> >
{
  static const char* value()
  {
    return "37feea1cd0d627db0c18584be77b9973";
  }

  static const char* value(const ::pangyo_control::ControlCommand_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x37feea1cd0d627dbULL;
  static const uint64_t static_value2 = 0x0c18584be77b9973ULL;
};

template<class ContainerAllocator>
struct DataType< ::pangyo_control::ControlCommand_<ContainerAllocator> >
{
  static const char* value()
  {
    return "pangyo_control/ControlCommand";
  }

  static const char* value(const ::pangyo_control::ControlCommand_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::pangyo_control::ControlCommand_<ContainerAllocator> >
{
  static const char* value()
  {
    return "uint16 gear\n\
uint16 speed\n\
float32 steer\n\
uint16 brake\n\
";
  }

  static const char* value(const ::pangyo_control::ControlCommand_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::pangyo_control::ControlCommand_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.gear);
      stream.next(m.speed);
      stream.next(m.steer);
      stream.next(m.brake);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct ControlCommand_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::pangyo_control::ControlCommand_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::pangyo_control::ControlCommand_<ContainerAllocator>& v)
  {
    s << indent << "gear: ";
    Printer<uint16_t>::stream(s, indent + "  ", v.gear);
    s << indent << "speed: ";
    Printer<uint16_t>::stream(s, indent + "  ", v.speed);
    s << indent << "steer: ";
    Printer<float>::stream(s, indent + "  ", v.steer);
    s << indent << "brake: ";
    Printer<uint16_t>::stream(s, indent + "  ", v.brake);
  }
};

} // namespace message_operations
} // namespace ros

#endif // PANGYO_CONTROL_MESSAGE_CONTROLCOMMAND_H
