////////////////////////////////////////////////////////////////////
/////////////////// SOL UNDER SIEGE ////////////////////////////////
///////////////////   Code Readme //////////////////////////////////
///////////////////   Last updated: 2020-03-02 /////////////////////
///////////////////   Author: Kyle Taylor Lange ////////////////////
////////////////////////////////////////////////////////////////////

  Sol Under Siege is a first-person shooter game created by me, Kyle Taylor Lange, in the Unreal Engine 4.
It has been in on/off development since 2015, and it is set throughout the planets and moons of the Solar
System as war and rebellion envelop them. Its goal is to blend the sense of realism in games like ARMA and
Red Orchestra with sci-fi environments and technology, and the gameplay will span small arena-style levels
for small-scale deathmatch to large open-terrain battlefields for objective-based big team battles.

  A larger document will serve as an instruction manual for the game that will better document its current 
development state, but the game should be considered "pre-alpha" with multiple bugs and incomplete 
features. It is currently only being distributed to potential employers and internships as an example of
my programming skills. Almost all graphics are very simple placeholders. I intend to publicly release the
game once more core features are complete and more thorougly tested.

  The game originally went under a working title "Lastim" that is still reflected in the name of the core 
module and certain classes that may be deleted or heavily modified in the future. Most of these references 
have already been replaced, e.g. "LastimGameMode" being renamed to "SolGameMode".

  All code has been written by me with the exception of sections taken or inspired by the source code from
the ShooterGame example project and Unreal Tournament (4). Most of those code sections involve the Slate-
based HUD elements (like the scoreboard), the infrastructure for creating network games, and some menu items
(like the key bindings), though the ShooterGame example project still has influence on parts of some weapon 
and game mode code since I largely figured out how the Unreal Engine worked by playing with that example 
project.
  