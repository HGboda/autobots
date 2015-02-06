/* Software License Agreement (BSD License)
 *
 * Copyright (c) 2011, Willow Garage, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above
 *    copyright notice, this list of conditions and the following
 *    disclaimer in the documentation and/or other materials provided
 *    with the distribution.
 *  * Neither the name of Willow Garage, Inc. nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * Auto-generated by genmsg_cpp from file /home/zhili/hector_slam_tutorial/auto_car_slam/src/rosserial/rosserial_arduino/msg/Adc.msg
 *
 */


#ifndef ROSSERIAL_ARDUINO_MESSAGE_ADC_H
#define ROSSERIAL_ARDUINO_MESSAGE_ADC_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace rosserial_arduino
{
template <class ContainerAllocator>
struct Adc_
{
  typedef Adc_<ContainerAllocator> Type;

  Adc_()
    : adc0(0)
    , adc1(0)
    , adc2(0)
    , adc3(0)
    , adc4(0)
    , adc5(0)  {
    }
  Adc_(const ContainerAllocator& _alloc)
    : adc0(0)
    , adc1(0)
    , adc2(0)
    , adc3(0)
    , adc4(0)
    , adc5(0)  {
    }



   typedef uint16_t _adc0_type;
  _adc0_type adc0;

   typedef uint16_t _adc1_type;
  _adc1_type adc1;

   typedef uint16_t _adc2_type;
  _adc2_type adc2;

   typedef uint16_t _adc3_type;
  _adc3_type adc3;

   typedef uint16_t _adc4_type;
  _adc4_type adc4;

   typedef uint16_t _adc5_type;
  _adc5_type adc5;




  typedef boost::shared_ptr< ::rosserial_arduino::Adc_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::rosserial_arduino::Adc_<ContainerAllocator> const> ConstPtr;
  boost::shared_ptr<std::map<std::string, std::string> > __connection_header;

}; // struct Adc_

typedef ::rosserial_arduino::Adc_<std::allocator<void> > Adc;

typedef boost::shared_ptr< ::rosserial_arduino::Adc > AdcPtr;
typedef boost::shared_ptr< ::rosserial_arduino::Adc const> AdcConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::rosserial_arduino::Adc_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::rosserial_arduino::Adc_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace rosserial_arduino

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}
// {'rosserial_arduino': ['/home/zhili/hector_slam_tutorial/auto_car_slam/src/rosserial/rosserial_arduino/msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::rosserial_arduino::Adc_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::rosserial_arduino::Adc_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::rosserial_arduino::Adc_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::rosserial_arduino::Adc_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::rosserial_arduino::Adc_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::rosserial_arduino::Adc_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::rosserial_arduino::Adc_<ContainerAllocator> >
{
  static const char* value()
  {
    return "6d7853a614e2e821319068311f2af25b";
  }

  static const char* value(const ::rosserial_arduino::Adc_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x6d7853a614e2e821ULL;
  static const uint64_t static_value2 = 0x319068311f2af25bULL;
};

template<class ContainerAllocator>
struct DataType< ::rosserial_arduino::Adc_<ContainerAllocator> >
{
  static const char* value()
  {
    return "rosserial_arduino/Adc";
  }

  static const char* value(const ::rosserial_arduino::Adc_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::rosserial_arduino::Adc_<ContainerAllocator> >
{
  static const char* value()
  {
    return "uint16 adc0\n\
uint16 adc1\n\
uint16 adc2\n\
uint16 adc3\n\
uint16 adc4\n\
uint16 adc5\n\
";
  }

  static const char* value(const ::rosserial_arduino::Adc_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::rosserial_arduino::Adc_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.adc0);
      stream.next(m.adc1);
      stream.next(m.adc2);
      stream.next(m.adc3);
      stream.next(m.adc4);
      stream.next(m.adc5);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER;
  }; // struct Adc_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::rosserial_arduino::Adc_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::rosserial_arduino::Adc_<ContainerAllocator>& v)
  {
    s << indent << "adc0: ";
    Printer<uint16_t>::stream(s, indent + "  ", v.adc0);
    s << indent << "adc1: ";
    Printer<uint16_t>::stream(s, indent + "  ", v.adc1);
    s << indent << "adc2: ";
    Printer<uint16_t>::stream(s, indent + "  ", v.adc2);
    s << indent << "adc3: ";
    Printer<uint16_t>::stream(s, indent + "  ", v.adc3);
    s << indent << "adc4: ";
    Printer<uint16_t>::stream(s, indent + "  ", v.adc4);
    s << indent << "adc5: ";
    Printer<uint16_t>::stream(s, indent + "  ", v.adc5);
  }
};

} // namespace message_operations
} // namespace ros

#endif // ROSSERIAL_ARDUINO_MESSAGE_ADC_H
