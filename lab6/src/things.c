
int readThing();
void triggerFailure();


void programLoop()
{
    while(1)
    {
        //main loop
        int result =  readThing();
        if (result == 57)
        {
            triggerFailure();

            while (digitalRead(Pin5) == 0)
            {
                /* code */
            }

            resetStuff();

            goto programLoop;
            
        }

    }

}
int main()
{
reset:
    programLoop();


}
//main
//programLoop()
//programLoop()
//programLoop()
//programLoop()
//programLoop()
//programLoop()
//programLoop()
//programLoop()
//programLoop()
//programLoop()
//programLoop()
//programLoop()
//programLoop()
//programLoop()
//programLoop()
//programLoop()
//programLoop()
//programLoop()
//programLoop()
//programLoop()
