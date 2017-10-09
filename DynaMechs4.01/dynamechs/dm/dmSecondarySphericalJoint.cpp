/*****************************************************************************
 * DynaMechs: A Multibody Dynamic Simulation Library
 *
 * Copyright (C) 1994-2001  Scott McMillan   All Rights Reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the Free
 * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *****************************************************************************
 *     File: dmSecondarySphericalJoint.cpp
 *   Author: Duane Marhefka
 *  Created: 1999
 *  Summary: Class declaration for spherical secondary joints.
 *****************************************************************************/

#include <dmSecondarySphericalJoint.hpp>

//============================================================================
// class dmSecondarySphericalJoint : public dmSecondaryJoint
//============================================================================


//----------------------------------------------------------------------------
//    Summary: constructor for dmSecondarySphericalJoint class
// Parameters: none
//    Returns: none
//----------------------------------------------------------------------------
dmSecondarySphericalJoint::dmSecondarySphericalJoint() : dmSecondaryJoint()
{
   for (int i = 0; i < NUM_DOFS; i++)
   {
      m_joint_input[i] = 0.0;
   }
}

//----------------------------------------------------------------------------
//    Summary: Set parameters for implementing the constraints.  The meaning
//             and use of the parameters depends on the type of secondary
//             joint.  For compliant (soft) joints, the terms are the linear
//             springs and dampers which implement the joint constraints.
//             For hard joints with spring/damper stabiliation, the
//             terms are the springs and dampers which implement the
//             constraint stabilization.  For hard joints with Baumgarte
//             stabilization, the terms are interpreted as the Baumgarte
//             coefficients. 
// Parameters: linear_spring - coefficient of linear proportional terms
//             linear_damper - coefficient of linear derivative terms
//    Returns: none
//----------------------------------------------------------------------------
void dmSecondarySphericalJoint::setConstraintParams(Float linear_spring,
                                                    Float linear_damper)
{
   m_pos_spring = linear_spring;
   m_pos_damper = linear_damper;
}


//----------------------------------------------------------------------------
//    Summary: retrieve the free joint position and velocity
// Parameters: none
//    Returns: q - orientation of joint specified by a rotation matrix
//             qd - angular velocity across joint
//----------------------------------------------------------------------------
void dmSecondarySphericalJoint::getFreeState(Float q[], Float qd[]) const
{
   register int i;

   for (i = 0; i < 3; i++)
   {
      q[0+i] = m_oa_R_k[0][i];
      q[3+i] = m_oa_R_k[1][i];
      q[6+i] = m_oa_R_k[2][i];

      qd[i] = m_k_w_rel[i];
   }
}

//----------------------------------------------------------------------------
//    Summary: retrieve the state of the joint constraints
// Parameters: none
//    Returns: q - array of constraint states
//             qd - array of constraint state derivatives
//----------------------------------------------------------------------------
void dmSecondarySphericalJoint::getConstrainedState(Float q[],
                                                    Float qd[]) const
{
   q[0] = m_d[0];
   q[1] = m_d[1];
   q[2] = m_d[2];

   qd[0] = m_d_dot[0];
   qd[1] = m_d_dot[1];
   qd[2] = m_d_dot[2];
}

//----------------------------------------------------------------------------
//    Summary: Compute the state (free and constrained) of the spherical
//             secondary joint.
// Parameters: none
//    Returns: none
//----------------------------------------------------------------------------
void dmSecondarySphericalJoint::computeState()
{
#ifdef DEBUG
   cout << "dmSecondarySphericalJoint::computeState() enter\n" << flush;
#endif

   // Compute state information common to all secondary joints.
   dmSecondaryJoint::computeState();

   /* Spherical joints have no specific information.  The orientation of
      the joint is given by dmSecondaryJoint::m_oa_R_k.  If needed in the 
      future, a state quaternion could be computed in this function.  The
      angular velocity state variables are given by 
      dmSecondaryJoint::m_k_w_rel.  */
}


//----------------------------------------------------------------------------
//    Summary: Computes and sets the eta_k1 and eta_k2 acceleration bias
//             terms which appear in the loop-closure constraint equation.
// Parameters: none
//    Returns: none
//----------------------------------------------------------------------------
void dmSecondarySphericalJoint::computeEtas()
{
#ifdef DEBUG
   cout << "dmSecondarySphericalJoint::computeEtas() enter\n" << flush;
#endif

   register int i;

   // Compute m_Eta_k1[0:2]

   // m_Eta_k1[0:2] = k_w_k x m_k_w_rel = (m_k_w_oa + m_k_w_rel) x m_k_w_rel
   //               = m_k_w_oa x m_k_w_rel
   crossproduct(m_k_w_oa, m_k_w_rel, &(m_Eta_k1[0]));

   // Compute m_Eta_k1[3:5]

   CartesianVector tmp1, tmp2, tmp3;
   crossproduct(m_oa_w_oa, m_d_dot, tmp1);
   crossproduct(m_oa_w_oa, m_d, tmp2);
   crossproduct(m_oa_w_oa, tmp2, tmp3);

   tmp3[0] += 2*tmp1[0];
   tmp3[1] += 2*tmp1[1];
   tmp3[2] += 2*tmp1[2];

   for (i = 0; i < 3; i++)
      m_Eta_k1[i+3] = (m_oa_R_k[0][i]*tmp3[0] +
                       m_oa_R_k[1][i]*tmp3[1] +
                       m_oa_R_k[2][i]*tmp3[2]);

   const dmABForKinStruct *kinStructA;
   kinStructA = m_articulation->getForKinStruct(m_link_A_index);
   crossproduct(kinStructA->v, m_a_p_oa, tmp1);
   crossproduct(kinStructA->v, tmp1, tmp2);

   for (i = 0; i < 3; i++)
      m_Eta_k1[i+3] += (m_a_R_k[0][i]*tmp2[0] +
                        m_a_R_k[1][i]*tmp2[1] +
                        m_a_R_k[2][i]*tmp2[2]);


   // Compute m_Eta_k2

   m_Eta_k2[0] = m_Eta_k2[1] = m_Eta_k2[2] = 0.0;

   const dmABForKinStruct *kinStructB;
   kinStructB = m_articulation->getForKinStruct(m_link_B_index);
   crossproduct(kinStructB->v, m_b_p_k, tmp1);
   crossproduct(kinStructB->v, tmp1, tmp2);

   for (i = 0; i < 3; i++)
      m_Eta_k2[i+3] = (m_b_R_k[0][i]*tmp2[0] +
                       m_b_R_k[1][i]*tmp2[1] +
                       m_b_R_k[2][i]*tmp2[2]);
}


//----------------------------------------------------------------------------
//    Summary: Computes the resultant force and moment applied
//             from link A to link B at the K coordinate system due
//             to the joint input and friction.
// Parameters: none  
//    Returns: none
//----------------------------------------------------------------------------
void dmSecondarySphericalJoint::computeAppliedForce()
{
   m_k_f_k[0] = m_joint_input[0] - m_joint_friction*m_k_w_rel[0];
   m_k_f_k[1] = m_joint_input[1] - m_joint_friction*m_k_w_rel[1];
   m_k_f_k[2] = m_joint_input[2] - m_joint_friction*m_k_w_rel[2];

   m_k_f_k[3] = m_k_f_k[4] = m_k_f_k[5] = 0.0;
}


//----------------------------------------------------------------------------
//    Summary: Adds the penalty force for a compliant (soft) secondary joint
//             to the applied forces at the joint.
// Parameters: none
//    Returns: none
//----------------------------------------------------------------------------
void dmSecondarySphericalJoint::applyPenaltyForce()
{
#ifdef DEBUG
   cerr << "dmSecondarySphericalJoint::applyPenaltyForce()" << flush << endl;
#endif

   register int i;

   CartesianVector slider_frc;

   // Compute the forces (in link A outboard coordinates).
   slider_frc[0] = -m_d[0]*m_pos_spring - m_d_dot[0]*m_pos_damper;
   slider_frc[1] = -m_d[1]*m_pos_spring - m_d_dot[1]*m_pos_damper;
   slider_frc[2] = -m_d[2]*m_pos_spring - m_d_dot[2]*m_pos_damper;

   // Convert the forces into K coordinates.
   for (i = 0; i < 3; i++)
      m_k_f_k[i+3] += (m_oa_R_k[0][i]*slider_frc[0] +
                       m_oa_R_k[1][i]*slider_frc[1] +
                       m_oa_R_k[2][i]*slider_frc[2]);
}


//----------------------------------------------------------------------------
//    Summary: Returns the forces of the constraint stabilization
//             springs and dampers (for hard constraints with spring and
//             damper constraint stabilization).
// Parameters: none
//    Returns: force - constraint stabilization forces and torques
//----------------------------------------------------------------------------
void dmSecondarySphericalJoint::computeStabilizationForce(Float force[])
{
   // Position forces.
   force[0] = -m_d[0]*m_pos_spring - m_d_dot[0]*m_pos_damper;
   force[1] = -m_d[1]*m_pos_spring - m_d_dot[1]*m_pos_damper;
   force[2] = -m_d[2]*m_pos_spring - m_d_dot[2]*m_pos_damper;
}


//----------------------------------------------------------------------------
//    Summary: Called prior to the AB backward dynamics routine to 
//             initialize the X_ik's for the secondary joint's
//             A link, B link, and the root link of the loop. 
// Parameters: link_index - index, i, of the link to compute Xik for
//             root_index - link index of the root of the loop closed by
//                          this secondary joint
//    Returns: Xik - coefficient of loop k's constraint forces in link
//                   i's force balance equation.  The transpose also
//                   appears loop k's constraint equations.
//----------------------------------------------------------------------------
void dmSecondarySphericalJoint::initXik(Float **Xik,
                                        int link_index,
                                        int root_index) const
{
   int i,j,r,c;

   if (link_index == m_link_A_index)  // Xik = X_p1(k)k
   {
      for (i = 0; i < 3; i++)
         for (j = 0; j < 3; j++)
            Xik[3+i][j] =  -m_a_R_oa[i][j];

      Xik[0][0] = -m_a_p_k[2]*Xik[4][0] + m_a_p_k[1]*Xik[5][0];
      Xik[0][1] = -m_a_p_k[2]*Xik[4][1] + m_a_p_k[1]*Xik[5][1];
      Xik[0][2] = -m_a_p_k[2]*Xik[4][2] + m_a_p_k[1]*Xik[5][2];

      Xik[1][0] =  m_a_p_k[2]*Xik[3][0] - m_a_p_k[0]*Xik[5][0];
      Xik[1][1] =  m_a_p_k[2]*Xik[3][1] - m_a_p_k[0]*Xik[5][1];
      Xik[1][2] =  m_a_p_k[2]*Xik[3][2] - m_a_p_k[0]*Xik[5][2];

      Xik[2][0] = -m_a_p_k[1]*Xik[3][0] + m_a_p_k[0]*Xik[4][0];
      Xik[2][1] = -m_a_p_k[1]*Xik[3][1] + m_a_p_k[0]*Xik[4][1];
      Xik[2][2] = -m_a_p_k[1]*Xik[3][2] + m_a_p_k[0]*Xik[4][2];
   }
   else if (link_index == m_link_B_index)  // Xik = X_p2(k)k
   {
      for (i = 0; i < 3; i++)
         for (j = 0; j < 3; j++)
            Xik[3+i][j] =  (m_b_R_k[i][0]*m_oa_R_k[j][0] +
                            m_b_R_k[i][1]*m_oa_R_k[j][1] +
                            m_b_R_k[i][2]*m_oa_R_k[j][2]);

      Xik[0][0] = -m_b_p_k[2]*Xik[4][0] + m_b_p_k[1]*Xik[5][0];
      Xik[0][1] = -m_b_p_k[2]*Xik[4][1] + m_b_p_k[1]*Xik[5][1];
      Xik[0][2] = -m_b_p_k[2]*Xik[4][2] + m_b_p_k[1]*Xik[5][2];

      Xik[1][0] =  m_b_p_k[2]*Xik[3][0] - m_b_p_k[0]*Xik[5][0];
      Xik[1][1] =  m_b_p_k[2]*Xik[3][1] - m_b_p_k[0]*Xik[5][1];
      Xik[1][2] =  m_b_p_k[2]*Xik[3][2] - m_b_p_k[0]*Xik[5][2];

      Xik[2][0] = -m_b_p_k[1]*Xik[3][0] + m_b_p_k[0]*Xik[4][0];
      Xik[2][1] = -m_b_p_k[1]*Xik[3][1] + m_b_p_k[0]*Xik[4][1];
      Xik[2][2] = -m_b_p_k[1]*Xik[3][2] + m_b_p_k[0]*Xik[4][2];
   }
   else if (link_index == root_index)  // Clear Xik for accumulation.
   {
      for (r = 0; r < 6; r++)
         for (c = 0; c < 3; c++)
            Xik[r][c] = 0.0;
   }
}


//----------------------------------------------------------------------------
//    Summary: Compute the acceleration bias term in the loop-closure
//             constraint equation.
// Parameters: none
//    Returns: zeta - the acceleration bias term  
//----------------------------------------------------------------------------
void dmSecondarySphericalJoint::getZeta(Float *zeta) const
{
   SpatialVector eta;
   eta[3] = m_Eta_k1[3] - m_Eta_k2[3];
   eta[4] = m_Eta_k1[4] - m_Eta_k2[4];
   eta[5] = m_Eta_k1[5] - m_Eta_k2[5];

   zeta[0] = m_oa_R_k[0][0]*eta[3] + m_oa_R_k[0][1]*eta[4] +
      m_oa_R_k[0][2]*eta[5];
   zeta[1] = m_oa_R_k[1][0]*eta[3] + m_oa_R_k[1][1]*eta[4] +
      m_oa_R_k[1][2]*eta[5];
   zeta[2] = m_oa_R_k[2][0]*eta[3] + m_oa_R_k[2][1]*eta[4] +
      m_oa_R_k[2][2]*eta[5];

   if (m_stabilization == BAUMGARTE)
   {
      // Add Baumgarte stabilization terms to zeta.
      zeta[0] += -m_d[0]*m_pos_spring - m_d_dot[0]*m_pos_damper;
      zeta[1] += -m_d[1]*m_pos_spring - m_d_dot[1]*m_pos_damper;
      zeta[2] += -m_d[2]*m_pos_spring - m_d_dot[2]*m_pos_damper;
   }
}
