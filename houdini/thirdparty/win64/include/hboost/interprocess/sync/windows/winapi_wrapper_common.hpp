 //////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2011-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef HBOOST_INTERPROCESS_DETAIL_WINAPI_WRAPPER_COMMON_HPP
#define HBOOST_INTERPROCESS_DETAIL_WINAPI_WRAPPER_COMMON_HPP

#ifndef HBOOST_CONFIG_HPP
#  include <hboost/config.hpp>
#endif
#
#if defined(HBOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <hboost/interprocess/detail/config_begin.hpp>
#include <hboost/interprocess/detail/workaround.hpp>
#include <hboost/interprocess/detail/win32_api.hpp>
#include <hboost/interprocess/detail/posix_time_types_wrk.hpp>
#include <hboost/interprocess/errors.hpp>
#include <hboost/interprocess/exceptions.hpp>
#include <limits>

namespace hboost {
namespace interprocess {
namespace ipcdetail {

inline void winapi_wrapper_wait_for_single_object(void *handle)
{
   unsigned long ret = winapi::wait_for_single_object(handle, winapi::infinite_time);
   if(ret != winapi::wait_object_0){
      if(ret != winapi::wait_abandoned){
         error_info err = system_error_code();
         throw interprocess_exception(err);
      }
      else{ //Special case for orphaned mutexes
         winapi::release_mutex(handle);
         throw interprocess_exception(owner_dead_error);
      }
   }
}

inline bool winapi_wrapper_try_wait_for_single_object(void *handle)
{
   unsigned long ret = winapi::wait_for_single_object(handle, 0);
   if(ret == winapi::wait_object_0){
      return true;
   }
   else if(ret == winapi::wait_timeout){
      return false;
   }
   else{
      error_info err = system_error_code();
      throw interprocess_exception(err);
   }
}

inline bool winapi_wrapper_timed_wait_for_single_object(void *handle, const hboost::posix_time::ptime &abs_time)
{
   //Windows does not support infinity abs_time so check it
   if(abs_time == hboost::posix_time::pos_infin){
      winapi_wrapper_wait_for_single_object(handle);
      return true;
   }
   const hboost::posix_time::ptime cur_time = microsec_clock::universal_time();
   //Windows uses relative wait times so check for negative waits
   //and implement as 0 wait to allow try-semantics as POSIX mandates.
   unsigned long ret = winapi::wait_for_single_object
      ( handle
      , (abs_time <= cur_time) ? 0u
                                 : (abs_time - cur_time).total_milliseconds()
      );
   if(ret == winapi::wait_object_0){
      return true;
   }
   else if(ret == winapi::wait_timeout){
      return false;
   }
   else{
      error_info err = system_error_code();
      throw interprocess_exception(err);
   }
}

}  //namespace ipcdetail {
}  //namespace interprocess {
}  //namespace hboost {

#include <hboost/interprocess/detail/config_end.hpp>

#endif   //HBOOST_INTERPROCESS_DETAIL_WINAPI_MUTEX_WRAPPER_HPP
