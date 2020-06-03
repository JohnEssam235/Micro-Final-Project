#include "uart.h"
#include "keypad.h"
void SystemInit(){} // dy function bt init el system kda bktbha w 5las..
	
// struct to store the rooms data		
struct rooms
{
   uint32_t number;  // room number...
	 uint32_t state;  // room state...
	// storing the password in 4 variables "4 numbers".................
   uint32_t pass1;
   uint32_t pass2;
   uint32_t pass3;
   uint32_t pass4;
};	

// assuming having 5 rooms
struct rooms arr[5];


uint32_t x;  // dummy variable...for putting clock on ports
	
	
/* variables used for taking the password from the client using keypad .......*/
uint32_t key1;
uint32_t key2;
uint32_t key3;
uint32_t key4;
/*...........................*/	

/* index of the chosen room...*/
uint32_t index;


/* state entered from pc.......*/
uint32_t room_state;

/* counter for the "for loop"...........*/
uint32_t a;
uint32_t i;

int main()
{
	// PUT CLOCK on PORTS A,D,F,C
	SYSCTL_RCGCGPIO_R |= (SYSCTL_RCGCGPIO_R0) | (SYSCTL_RCGCGPIO_R2) | (SYSCTL_RCGCGPIO_R3) | (SYSCTL_RCGCGPIO_R5);
	//consuming time till putting the clock..
	x = x+1;
	// ana 3mlt configure ll uart pins ely ana hst3mlhom(fe el uart_init) ...dlw2ty hzabat pins ll "keypad" w el "LED".......
	// first....keypad (PORTD,PORTC) pins...
	GPIO_PORTC_LOCK_R =0x4C4F434B;  // open lock for portC pins
  GPIO_PORTC_CR_R = 0xF0;
	GPIO_PORTD_LOCK_R =0x4C4F434B;  // open lock for portD pins...
  GPIO_PORTD_CR_R = 0x0F;
	
	// Make PortD pins act as digital pins...............
	GPIO_PORTD_DEN_R |= 0x0F;
	
	// Make PortC pins act as digital pins...............
  GPIO_PORTC_DEN_R |= 0xF0;

	GPIO_PORTD_PUR_R = 0X0F;  // internal pull up rows pins of keypad...................
	//second ...portf(LED).............
	// Awl 7aga h5leh b output w digital....w b3d kda el LED B "1" y3ny el lock mafto7 el awl.....lock is opened means LED is "ON"......
	GPIO_PORTF_LOCK_R =0x4C4F434B;  // open the lock...........
  GPIO_PORTF_CR_R = 0x02;
	SET_BIT(GPIO_PORTF_DEN_R,1); //led 1.......
	SET_BIT(GPIO_PORTF_DIR_R,1);
	
	SET_BIT(GPIO_PORTF_DATA_R,1);  // el awl el solenoid valve htb2a unlocked(room is open) ......
	UART_init();
	
	// take the room numbers from the reciptionist.................
	for(i=0;i<5;i++)
	{
		 arr[i].number = UART_recieveByte();
	}
	

	while(1)
	{
		uint32_t num = UART_recieveByte();
		for(a=0;a<5;a++)
		{
			 if(num == arr[a].number)
			 {
				 index = a; // determining the index of the chosen room.....
			 }
				 
		}
		// first check the state to determine what should i do...............
		room_state = UART_recieveByte();
		if(room_state == 0) // check out.....
		{
			// change state of the room
			arr[index].state = 0;
			
			// solenoid will be unlocked( =1 ).....open room...
      SET_BIT(GPIO_PORTF_DATA_R,1);

      // reset password.....
      arr[index].pass1 = 0;
      arr[index].pass2=0;
      arr[index].pass3=0;
      arr[index].pass4=0;			
						
		}
		else if(room_state == 1) //check in.......
		{
			 // change the room state  
			 arr[index].state = 1;
			 
			// close the room(lock)......
			CLEAR_BIT(GPIO_PORTF_DATA_R,1);
			
			 // take the password from the receptionist through UART and store it in the room password(taking the 4 numbers).....
		   arr[index].pass1 = UART_recieveByte();  // enter the password......
       arr[index].pass2=UART_recieveByte();
       arr[index].pass3=UART_recieveByte(); 		
       arr[index].pass4=UART_recieveByte();

       // after that the client will try to open the room using the keypad ....
        	key1 = KeyPad_getPressedKey();
          key2 = KeyPad_getPressedKey();
          key3 = KeyPad_getPressedKey(); 		
          key4 = KeyPad_getPressedKey();
 
        // then check if he/she has entered the right password or not...
        if((key1==arr[index].pass1) && (key2==arr[index].pass2) && (key3==arr[index].pass3) && (key4==arr[index].pass4))
				{
					// open the lock....
					SET_BIT(GPIO_PORTF_DATA_R,1);
				}
         else
				 {
					 // wrong password.......the lock remains closed as it is.......
				 }					 
			
		}
		else if(room_state==2) // room cleaning
		{
			
			// open the locked solenoid...
			SET_BIT(GPIO_PORTF_DATA_R,1);
			
			// change the room state...
			arr[index].state = 2;
			
		}
	}
}