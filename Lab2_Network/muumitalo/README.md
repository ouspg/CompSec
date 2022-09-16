# Muumitalo

## How to start

Can be run with docker by using the compose file in the main directory

## How to use

You find Muumipappa at the endpoint `localhost:3002/ovi`. You have to answer his question correctly in order to get
inside Muumitalo. The answering is done by sending a POST request to the endpoint. Content of the request should be in
the following format: 

`method: POST, url: localhost:3002/ovi?answer=vaapukkamehu`.

Example:

> curl -G -X POST -d "answer=vaapukkamehu" http://localhost:3002/ovi

### Task

After watching few too many hacker movies, Muumipappa became paranoid and started to think that Moominvalley's most
infamous hacker, Haisuli, was trying to steal a draft of his precious memoirs, so he decided to lock himself inside the
Muumitalo. Muumipappa said he will only open the door to people who know him well enough to guess his favourite drink.
Luckily you know that the correct answer is `vaapukkamehu`, but unfortunately the hacker film marathon also made
Pappa obsessed with "l33t 5p34k".

Your task is to get Muumipappa to open Muumitalo's door by sending him a POST request that contains the correct "l337
5p34ky" version of the word `vaapukkamehu`. You have to guess the right spelling of the word by trying different
mutations.

Attempt the following mutations:

* Change letters to lower/uppercase
* "l337 5p34k1fy" it. (The only characters you have to worry are a and e. A can potentially be 4 and e can be 3. The
  correct word could be for instance vA4PukKaM3hu).

Server will return 404 if you guessed wrong, 200 if you guessed right and something else if it breaks down due to
improper input.