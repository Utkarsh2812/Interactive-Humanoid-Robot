# Interactive-Humanoid-Robot
A Interactive System based Voice Controlled humanoid robot that can provide an interaction based Querry system and can perform trained gaits over voice command. The overall system works over the serial communication between arduino and python. 3 pre-defined gaits are added to the motions of the humanoid robot and keyword is assigned to each gait.

## Structure of the Humanoid Robot
![image](https://github.com/Utkarsh2812/Interactive-Humanoid-Robot/assets/91966216/9658566c-4a4b-449e-af15-4113b540dde9)

The Structure of the prototype is made up of assembling the MG995/96R servo motor brackets.

## Phase-1- The Movement of Upper Body of the robot to perform basic Upper body Gaits.

Circuit Diagram of the Robot for manipulating upper body motions

![image](https://github.com/Utkarsh2812/Interactive-Humanoid-Robot/assets/91966216/8ff36289-2429-4158-aee4-61618d25e9cc)

Three gaits over which robot was trained are:

1. Greeting Gait: The greetings gait was calibrated to facilitate friendly interactions between the robot and users. By implementing movement of hand over the body , we created a greeting gesture tailored towards  various social contexts. The gait raises its hands above its shoulder and waves continuously to greet the user.

![WhatsApp Image 2024-04-23 at 09 50 40_663f02e8](https://github.com/Utkarsh2812/Interactive-Humanoid-Robot/assets/91966216/97db7a64-7a38-4b71-b1cc-4db7b9a54953)

Motor Movement table for Greeting gait

![image](https://github.com/Utkarsh2812/Interactive-Humanoid-Robot/assets/91966216/8ab6f526-7fe3-447a-b0f0-90e2da2a930a)

2. Welcome Gait: The welcoming gait was designed to help the robot welcome the user into the premises. This gaits raises the hand towards the front  and moves the wrist in such a fashion that it looks like the robot is welcoming you.The robot successfully welcomes you.

![WhatsApp Image 2024-04-23 at 09 50 41_18ad2eab](https://github.com/Utkarsh2812/Interactive-Humanoid-Robot/assets/91966216/6bd00cb5-8622-44c8-b98a-d93d0170532c)

Motor Movement table for Welcome gait

![image](https://github.com/Utkarsh2812/Interactive-Humanoid-Robot/assets/91966216/58ac6fcb-0d2c-4ae6-a256-2f2117730cbb)

3. Dance Gait: The calibration process for the dance gait involved calibration of motors present on both its hands . By fine-tuning parameters such as joint angles, velocity profiles, and synchronization, we achieved smooth and synchronized dance movements. The robot successfully performed a dance routine.

![WhatsApp Image 2024-04-23 at 09 50 41_6713c499](https://github.com/Utkarsh2812/Interactive-Humanoid-Robot/assets/91966216/d70ff509-ee94-447b-bfc7-63c379c448ed)

Motor Movement table for Dance gait

![image](https://github.com/Utkarsh2812/Interactive-Humanoid-Robot/assets/91966216/34ab8a54-ab43-4c5f-a9d8-5d492a2da15f)

### Torque analysis of the gaits:

![image](https://github.com/Utkarsh2812/Interactive-Humanoid-Robot/assets/91966216/85b22b08-17df-48ec-830a-da7c9cf20c3c)
