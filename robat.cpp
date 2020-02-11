std::shared_ptr<NetworkTable> vision;

nt::NetworkTableInstance inst;
nt::NetworkTableEntry driverMode;

void Robot::RobotInit() {
  
        
    inst = nt::NetworkTableInstance::Create();
    inst.StartClient("10.55.61.50");
    inst.StartDSClient();
  
    vision  = inst.GetTable("chameleon-vision/camera");

    driverMode           = vision->GetEntry("driverMode"); 
}

void Robot::TeleopPeriodic() {
    
    if (joystcik.GetRawButton(1) == true)
    {
        vision->PutBoolean("driverMode", false);
        inst.Flush();
    }

    if (joystcik.GetRawButton(2) == true)
    {
        vision->PutBoolean("driverMode", true);
        inst.Flush();
    }

    frc::SmartDashboard::PutBoolean("driverMode",    driverMode.GetBoolean(false));

}