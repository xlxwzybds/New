#include "dram_perf_model_constant.h"
#include "simulator.h"
#include "config.h"
#include "config.hpp"
#include "stats.h"
#include "shmem_perf.h"
#include "dram_trace_collect.h" // Used to calculate the bank number from an address.

#define LOW_POWER 0
#define NORMAL_POWER 1

///XJY multi bank-mode ADD
#define POWER9 9 
#define POWER8 8
#define POWER7 7
#define POWER6 6 
#define POWER5 5 
///XJY multi bank-mode ADD ENDS


/*
   This file has been extended to support a low power access latency,
   which will be used when memory DTM is used.
*/

DramPerfModelConstant::DramPerfModelConstant(core_id_t core_id,
      UInt32 cache_block_size):
   DramPerfModel(core_id, cache_block_size),
   m_queue_model(NULL),
   m_dram_bandwidth(8 * Sim()->getCfg()->getFloat("perf_model/dram/per_controller_bandwidth")), // Convert bytes to bits
   m_total_queueing_delay(SubsecondTime::Zero()),
   m_total_access_latency(SubsecondTime::Zero())
{
   m_dram_access_cost = SubsecondTime::FS() * static_cast<uint64_t>(TimeConverter<float>::NStoFS(Sim()->getCfg()->getFloat("perf_model/dram/latency"))); // Operate in fs for higher precision before converting to uint64_t/SubsecondTime

   // Read the low power access cost.
   m_dram_access_cost_lowpower  = SubsecondTime::FS() * static_cast<uint64_t>(TimeConverter<float>::NStoFS(Sim()->getCfg()->getFloat("perf_model/dram/latency_lowpower"))); // Operate in fs for higher precision before converting to uint64_t/SubsecondTime
   ///XJY multi bank-mode ADD
   ///XJY multi bank-mode ADD
   ///XJY multi bank-mode ADD
   ///XJY multi bank-mode ADD
   m_dram_access_cost_power9  = SubsecondTime::FS() * static_cast<uint64_t>(TimeConverter<float>::NStoFS(Sim()->getCfg()->getFloat("perf_model/dram/latency_power9"))); 
   m_dram_access_cost_power8  = SubsecondTime::FS() * static_cast<uint64_t>(TimeConverter<float>::NStoFS(Sim()->getCfg()->getFloat("perf_model/dram/latency_power8"))); 
   m_dram_access_cost_power7  = SubsecondTime::FS() * static_cast<uint64_t>(TimeConverter<float>::NStoFS(Sim()->getCfg()->getFloat("perf_model/dram/latency_power7"))); 
   m_dram_access_cost_power6  = SubsecondTime::FS() * static_cast<uint64_t>(TimeConverter<float>::NStoFS(Sim()->getCfg()->getFloat("perf_model/dram/latency_power6"))); 
   m_dram_access_cost_power5  = SubsecondTime::FS() * static_cast<uint64_t>(TimeConverter<float>::NStoFS(Sim()->getCfg()->getFloat("perf_model/dram/latency_power5"))); 
   ///XJY multi bank-mode ADD ENDS
   ///XJY multi bank-mode ADD ENDS
   ///XJY multi bank-mode ADD ENDS
   ///XJY multi bank-mode ADD ENDS

   if (Sim()->getCfg()->getBool("perf_model/dram/queue_model/enabled"))
   {
      m_queue_model = QueueModel::create("dram-queue", core_id, Sim()->getCfg()->getString("perf_model/dram/queue_model/type"),
                                         m_dram_bandwidth.getRoundedLatency(8 * cache_block_size)); // bytes to bits
   }

   registerStatsMetric("dram", core_id, "total-access-latency", &m_total_access_latency);
   registerStatsMetric("dram", core_id, "total-queueing-delay", &m_total_queueing_delay);
}

DramPerfModelConstant::~DramPerfModelConstant()
{
   if (m_queue_model)
   {
     delete m_queue_model;
      m_queue_model = NULL;
   }
}

SubsecondTime
DramPerfModelConstant::getAccessLatency(SubsecondTime pkt_time, UInt64 pkt_size, core_id_t requester, IntPtr address, DramCntlrInterface::access_t access_type, ShmemPerf *perf)
{
   // pkt_size is in 'Bytes'
   // m_dram_bandwidth is in 'Bits per clock cycle'
   if ((!m_enabled) ||
         (requester >= (core_id_t) Config::getSingleton()->getApplicationCores()))
   {
      return SubsecondTime::Zero();
   }

   SubsecondTime processing_time = m_dram_bandwidth.getRoundedLatency(8 * pkt_size); // bytes to bits

   // Compute Queue Delay
   SubsecondTime queue_delay;
   if (m_queue_model)
   {
      queue_delay = m_queue_model->computeQueueDelay(pkt_time, processing_time, requester);
   }
   else
   {
      queue_delay = SubsecondTime::Zero();
   }

   UInt32 bank_nr = get_address_bank(address, requester);
   int bank_mode = Sim()->m_bank_modes[bank_nr];

   SubsecondTime access_latency;

   // Distinguish between dram power modes.
   // ///XJY multi bank-mode ADD
   // ///XJY multi bank-mode ADD
   // ///XJY multi bank-mode ADD
   // ///XJY multi bank-mode ADD
   if (bank_mode == LOW_POWER) // Low power mode
   {
      access_latency = queue_delay + processing_time + m_dram_access_cost_lowpower;
   }
   //else // Normal power mode.
   else if( bank_mode ==  POWER9)
   {
      access_latency = queue_delay + processing_time + m_dram_access_cost_power9;
   }
   else if( bank_mode ==  POWER8)
   {
      access_latency = queue_delay + processing_time + m_dram_access_cost_power8;
   }
   else if( bank_mode ==  POWER7)
   {
      access_latency = queue_delay + processing_time + m_dram_access_cost_power7;
   }
   else if( bank_mode ==  POWER6)
   {
      access_latency = queue_delay + processing_time + m_dram_access_cost_power6;
   }
   else if( bank_mode ==  POWER5)
   {
      access_latency = queue_delay + processing_time + m_dram_access_cost_power5;
   }
   else if (bank_mode == NORMAL_POWER) // Normal power mode.
   {
      access_latency = queue_delay + processing_time + m_dram_access_cost;
   }
   ///XJY multi bank-mode ADD ENDS
   ///XJY multi bank-mode ADD ENDS
   ///XJY multi bank-mode ADD ENDS
   ///XJY multi bank-mode ADD ENDS

   perf->updateTime(pkt_time);
   perf->updateTime(pkt_time + queue_delay, ShmemPerf::DRAM_QUEUE);
   perf->updateTime(pkt_time + queue_delay + processing_time, ShmemPerf::DRAM_BUS);
   perf->updateTime(pkt_time + queue_delay + processing_time + m_dram_access_cost, ShmemPerf::DRAM_DEVICE);

   // Update Memory Counters
   m_num_accesses ++;
   m_total_access_latency += access_latency;
   m_total_queueing_delay += queue_delay;

   return access_latency;
}
