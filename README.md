# VEX-6-mtr-Drivetrain
Hi
How are you doing?

So, it would be a good idea to open this with the VEXcode Pro V5
("This" means the 2 files of code in the main code files. You should use the entire parent folder though.)
Anyways, the Red-[...].v5code, methinks is the code all in one line although I never
opened it
main.cpp is the main code with the competition template. It has
the pre-auton, auton, and use control.
I made the bang-bang control. Which is kind of like PID control but not as good. (with GPT, ofc)
It is horrible and doesn't work, but it is a problem for another day.
but the main knocker outer is the robot-config.cpp. It is what I have trouble with.
The big code at the bottom is the auto-code that is put there once you add a 4 mtr drivetrain
with the controller stating that I want arcade drive.
All I did was add one line adding the 5th and 6th motors wherever it mentions the drivetrain
But for some reason, it is pivoting while turning
which means that one side is moving forward, while the other isn't moving at all
I wanta  swing turn. That is when one side moves backward while the other moves forward.
I was following this video for arcade drive
https://www.youtube.com/watch?v=piBOl5yHJ_c&t=1573s
when I do an arcade drive, it doesn't move at all...
But the tank drive works perfectly!
Thanks for your help.
And thanks for opening this README for a bit of background

---

Pretty good. Its a friday - I did my time and now I get to play some video games. Took a look at the project.
Its going to be difficult to diagnose what you have going wrong as it looks like you're doing a mix of
C++ and Code No Code. This relies on source files and using a gui that is like... not cash money. And my method of
debugging is log statements mostly. I mean I've used a debugger I know how, but print statements are your friend.
Anyways motor groups can be as big as you want them to be. That might help in the initial degugging phase.
After that I would recommend adding and testing in smaller chunks. When it stops working figure out why.
Cheers
Travis Kohler
