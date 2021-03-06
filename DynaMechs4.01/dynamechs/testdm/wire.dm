# DynaMechs V 2.0.3 ascii
# tree parameter file

Graphics_Models {
	Number_Graphics_Models  3
	"../models/sm_cube_center.xan"
	"../models/sm_cube_center2.xan"
	"../models/obj_cylinder_x_slim.xan"
}

System {
    StaticRefMember {
	Graphics_Model_Index	 0

	Position	  20.0   0.0   2.0
	Orientation_Quat  0.0 0.0 0.0 1.0
    }

    Articulation {

	# Initial axial translation for control (the "push/pull" joint)
	PrismaticLink {
	    Graphics_Model_Index	 0

	    Mass			 0.1
	    Inertia			 0.1   0.0  0.0
					 0.0   0.1  0.0
					 0.0   0.0  0.1
	    Center_of_Gravity		 0.0 0.0 0.0

	    Number_of_Contact_Points	 0

	    MDH_Parameters		 0.0 -1.5708 0.0 0.0
	    Initial_Joint_Velocity	 0.0
	    Joint_Limits		-20.0 20.0 
	    Joint_Limit_Spring_Constant  50.0
	    Joint_Limit_Damper_Constant  5.0

	    Joint_Friction		 0.35
	}

	# Initial axial roll joint for control (the "twist" joint)
	RevoluteLink {
	    Graphics_Model_Index	 0

	    Mass			 0.1
	    Inertia			 0.1   0.0  0.0
					 0.0   0.1  0.0
					 0.0   0.0  0.1
	    Center_of_Gravity		 0.0 0.0 0.0

	    Number_of_Contact_Points	 0

	    MDH_Parameters		 0.0 0.0 0.0 0.50
	    Initial_Joint_Velocity	 0.0
	    Joint_Limits		-10.172 10.172 
	    Joint_Limit_Spring_Constant  50.0
	    Joint_Limit_Damper_Constant  5.0

	    Actuator_Type		 0
	    Joint_Friction		 0.35
	}

	# This link pair is different from the rest that follow but
	# they still represent a universal joint

	# Element 1a - almost a massless, extent-less joint
	RevoluteLink {
	    Graphics_Model_Index	 1

	    Mass			 0.01
	    Inertia			 0.01  0.0  0.0
					 0.0   0.01 0.0
					 0.0   0.0  0.01
	    Center_of_Gravity		 0.0 0.0 0.0

	    Number_of_Contact_Points	 0

	    MDH_Parameters		 0.0 1.5708 0.0 1.5708
	    Initial_Joint_Velocity	 0.0
	    Joint_Limits		 1.5708 1.5708
	    Joint_Limit_Spring_Constant  50.0
	    Joint_Limit_Damper_Constant  5.0

	    Actuator_Type		 0
	    Joint_Friction		 0.35
	}

	# Element 1b - a wire element with mass and length (3.0)
	RevoluteLink {
	    Graphics_Model_Index	 2

	    Mass			 0.5
	    Inertia			 0.1   0.0  0.0
					 0.0   1.7  0.0
					 0.0   0.0  1.7
	    Center_of_Gravity		 1.5 0.0 0.0

	    Number_of_Contact_Points	 1
	    Contact_Locations		 3.0  0.0  0.0

	    MDH_Parameters		 0.0 1.5708 0.0 0.0
	    Initial_Joint_Velocity	 0.0
	    Joint_Limits		 0.0 0.0
	    Joint_Limit_Spring_Constant  50.0
	    Joint_Limit_Damper_Constant  5.0

	    Actuator_Type		 0
	    Joint_Friction		 0.35
	}

	# The following two are the repeating pairs corresponding to 2DOF
	# wire elements.

	# Element 2a - nearly massless, extent-less
	RevoluteLink {
	    Graphics_Model_Index	 1

	    Mass			 0.01
	    Inertia			 0.01  0.0  0.0
					 0.0   0.01 0.0
					 0.0   0.0  0.01
	    Center_of_Gravity		 0.0 0.0 0.0

	    Number_of_Contact_Points	 0

	    MDH_Parameters		 3.0 -1.5708 0.0 0.0
	    Initial_Joint_Velocity	 0.0
	    Joint_Limits		 0.0 0.0
	    Joint_Limit_Spring_Constant  50.0
	    Joint_Limit_Damper_Constant  5.0

	    Actuator_Type		 0
	    Joint_Friction		 0.35
	}

	# Element 2b - wire element
	RevoluteLink {
	    Graphics_Model_Index	 2

	    Mass			 0.5
	    Inertia			 0.1   0.0  0.0
					 0.0   1.7  0.0
					 0.0   0.0  1.7
	    Center_of_Gravity		 1.5 0.0 0.0

	    Number_of_Contact_Points	 1
	    Contact_Locations		 3.0  0.0  0.0

	    MDH_Parameters		 0.0 1.5708 0.0 0.0
	    Initial_Joint_Velocity	 0.0
	    Joint_Limits		 0.0 0.0
	    Joint_Limit_Spring_Constant  50.0
	    Joint_Limit_Damper_Constant  5.0

	    Actuator_Type		 0
	    Joint_Friction		 0.35
	}

	# Element 2a - nearly massless, extent-less
	RevoluteLink {
	    Graphics_Model_Index	 1

	    Mass			 0.01
	    Inertia			 0.01  0.0  0.0
					 0.0   0.01 0.0
					 0.0   0.0  0.01
	    Center_of_Gravity		 0.0 0.0 0.0

	    Number_of_Contact_Points	 0

	    MDH_Parameters		 3.0 -1.5708 0.0 0.0
	    Initial_Joint_Velocity	 0.0
	    Joint_Limits		 0.0 0.0
	    Joint_Limit_Spring_Constant  50.0
	    Joint_Limit_Damper_Constant  5.0

	    Actuator_Type		 0
	    Joint_Friction		 0.35
	}

	# Element 2b - wire element
	RevoluteLink {
	    Graphics_Model_Index	 2

	    Mass			 0.5
	    Inertia			 0.1   0.0  0.0
					 0.0   1.7  0.0
					 0.0   0.0  1.7
	    Center_of_Gravity		 1.5 0.0 0.0

	    Number_of_Contact_Points	 1
	    Contact_Locations		 3.0  0.0  0.0

	    MDH_Parameters		 0.0 1.5708 0.0 0.0
	    Initial_Joint_Velocity	 0.0
	    Joint_Limits		 0.0 0.0
	    Joint_Limit_Spring_Constant  50.0
	    Joint_Limit_Damper_Constant  5.0

	    Actuator_Type		 0
	    Joint_Friction		 0.35
	}

	# Element 2a - nearly massless, extent-less
	RevoluteLink {
	    Graphics_Model_Index	 1

	    Mass			 0.01
	    Inertia			 0.01  0.0  0.0
					 0.0   0.01 0.0
					 0.0   0.0  0.01
	    Center_of_Gravity		 0.0 0.0 0.0

	    Number_of_Contact_Points	 0

	    MDH_Parameters		 3.0 -1.5708 0.0 0.0
	    Initial_Joint_Velocity	 0.0
	    Joint_Limits		 0.0 0.0
	    Joint_Limit_Spring_Constant  50.0
	    Joint_Limit_Damper_Constant  5.0

	    Actuator_Type		 0
	    Joint_Friction		 0.35
	}

	# Element 2b - wire element
	RevoluteLink {
	    Graphics_Model_Index	 2

	    Mass			 0.5
	    Inertia			 0.1   0.0  0.0
					 0.0   1.7  0.0
					 0.0   0.0  1.7
	    Center_of_Gravity		 1.5 0.0 0.0

	    Number_of_Contact_Points	 1
	    Contact_Locations		 3.0  0.0  0.0

	    MDH_Parameters		 0.0 1.5708 0.0 0.0
	    Initial_Joint_Velocity	 0.0
	    Joint_Limits		 0.0 0.0
	    Joint_Limit_Spring_Constant  50.0
	    Joint_Limit_Damper_Constant  5.0

	    Actuator_Type		 0
	    Joint_Friction		 0.35
	}

	# Element 2a - nearly massless, extent-less
	RevoluteLink {
	    Graphics_Model_Index	 1

	    Mass			 0.01
	    Inertia			 0.01  0.0  0.0
					 0.0   0.01 0.0
					 0.0   0.0  0.01
	    Center_of_Gravity		 0.0 0.0 0.0

	    Number_of_Contact_Points	 0

	    MDH_Parameters		 3.0 -1.5708 0.0 0.0
	    Initial_Joint_Velocity	 0.0
	    Joint_Limits		 0.0 0.0
	    Joint_Limit_Spring_Constant  50.0
	    Joint_Limit_Damper_Constant  5.0

	    Actuator_Type		 0
	    Joint_Friction		 0.35
	}

	# Element 2b - wire element
	RevoluteLink {
	    Graphics_Model_Index	 2

	    Mass			 0.5
	    Inertia			 0.1   0.0  0.0
					 0.0   1.7  0.0
					 0.0   0.0  1.7
	    Center_of_Gravity		 1.5 0.0 0.0

	    Number_of_Contact_Points	 1
	    Contact_Locations		 3.0  0.0  0.0

	    MDH_Parameters		 0.0 1.5708 0.0 0.0
	    Initial_Joint_Velocity	 0.0
	    Joint_Limits		 0.0 0.0
	    Joint_Limit_Spring_Constant  50.0
	    Joint_Limit_Damper_Constant  5.0

	    Actuator_Type		 0
	    Joint_Friction		 0.35
	}

	# Element 2a - nearly massless, extent-less
	RevoluteLink {
	    Graphics_Model_Index	 1

	    Mass			 0.01
	    Inertia			 0.01  0.0  0.0
					 0.0   0.01 0.0
					 0.0   0.0  0.01
	    Center_of_Gravity		 0.0 0.0 0.0

	    Number_of_Contact_Points	 0

	    MDH_Parameters		 3.0 -1.5708 0.0 0.0
	    Initial_Joint_Velocity	 0.0
	    Joint_Limits		 0.0 0.0
	    Joint_Limit_Spring_Constant  50.0
	    Joint_Limit_Damper_Constant  5.0

	    Actuator_Type		 0
	    Joint_Friction		 0.35
	}

	# Element 2b - wire element
	RevoluteLink {
	    Graphics_Model_Index	 2

	    Mass			 0.5
	    Inertia			 0.1   0.0  0.0
					 0.0   1.7  0.0
					 0.0   0.0  1.7
	    Center_of_Gravity		 1.5 0.0 0.0

	    Number_of_Contact_Points	 1
	    Contact_Locations		 3.0  0.0  0.0

	    MDH_Parameters		 0.0 1.5708 0.0 0.0
	    Initial_Joint_Velocity	 0.0
	    Joint_Limits		 0.0 0.0
	    Joint_Limit_Spring_Constant  50.0
	    Joint_Limit_Damper_Constant  5.0

	    Actuator_Type		 0
	    Joint_Friction		 0.35
	}
    }
}
