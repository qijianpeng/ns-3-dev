/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include "ns3/computation-model-helper.h"
#include "ns3/computation-model.h"
#include "ns3/config.h"
#include "ns3/names.h"
#include "ns3/log.h"
#include "ns3/pointer.h"
#include "ns3/string.h"
#include <iostream>

namespace ns3 {

ComputationHelper::ComputationHelper()
{
    m_computationFactory.SetTypeId("ns3::SimpleComputationModel");
}

ComputationHelper::~ComputationHelper()
{
}

void ComputationHelper::Install(Ptr<Node> node) const
{
  NS_ASSERT(node != NULL);
  Ptr<Object> object = node;
  //TODO(qjp): Use a container instead of ComputationModel. Computation resources can be CPU, GPU
  //           or any others.
  Ptr<ComputationModel> model = object->GetObject<ComputationModel>();
  if(model == 0)//if empty or nullptr
  {
    //m_computationFactory already setted in ComputationHelper::ComputationHelper().
    model = m_computationFactory.Create()->GetObject<ComputationModel>();
    if(model == 0)
    {
      NS_FATAL_ERROR("The requested computation model is not a computation mode: \"" <<
                    m_computationFactory.GetTypeId().GetName() << "\"");
    }
    model->SetNode(node);
    object->AggregateObject(model);
  }
}

void ComputationHelper::Install(NodeContainer c) const
{
  for (NodeContainer::Iterator i = c.Begin (); i != c.End (); ++i)
  {
    Install(*i);
  }
}

void ComputationHelper::Install(std::string nodeName) const
{
  Ptr<Node> node = Names::Find<Node> (nodeName);
  Install(node);
}

void ComputationHelper::InstallAll(void)
{
  Install(NodeContainer::GetGlobal());
}

void ComputationHelper::SetComputationModel(std::string type)
{
  m_computationFactory.SetTypeId(type);
}
}

