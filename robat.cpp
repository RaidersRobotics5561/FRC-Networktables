//Creates a table of NT values
std::shared_ptr<NetworkTable> vision;

nt::NetworkTableInstance inst;

//Creates entry which can later be assigned to a table, only viewed by rio and dashboard
nt::NetworkTableEntry driverMode;
nt::NetworkTableEntry targetYaw;

void Robot::RobotInit() {
  
    //Creates instance of NT
    inst = nt::NetworkTableInstance::Create();
  
    //Tells rio the ip of the server to connect to
    inst.StartClient("10.55.61.50");
    inst.StartDSClient();
  
     //Acquires table from server
    vision  = inst.GetTable("chameleon-vision/camera");
    
    //Sets NT entry to some value from the NT server and assigns entry to a table
    driverMode = vision->GetEntry("driverMode");
    targetYaw  = vision->GetEntry("targetYaw");
}

void Robot::TeleopPeriodic() {
    
    if (joystick.GetRawButton(1) == true)
    {
        //Changes value of an entry in the table, then updates the table
        vision->PutBoolean("driverMode", false);
        inst.Flush();
    }

    if (joystick.GetRawButton(2) == true)
    {
        vision->PutBoolean("driverMode", true);
        inst.Flush();
    }

    frc::SmartDashboard::PutBoolean("driverMode", driverMode.GetBoolean(false));
    frc::SmartDashboard::PutBoolean("targetYaw", targetYaw.GetDouble(0));
    /* 
     *  Outputs NT entry to dashboard
     *  Important when using NT entry in code to use .GetXxxxx for variable type as shown
     */
}
