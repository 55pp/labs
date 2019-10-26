import Control.Concurrent
import Control.Monad (forever)
import Control.Concurrent.Chan
import System.Random
import System.IO.Unsafe

type Msg = String

initProc init_gm_ch gm_init_ch = do
  putStrLn "init: send start"
  writeChan init_gm_ch "i_start"
  putStrLn "init: wait answer"
  msg <- readChan gm_init_ch
  let modif = show(((read msg::Int) + 10))
  putStrLn $ "Score: " ++ modif

gmProc init_gm_ch gm_init_ch gm_player_ch player_gm_ch = do
  putStrLn "gm: wait message"
  msg <- readChan init_gm_ch
  putStrLn $  "gm: receive " ++ msg
  writeChan gm_player_ch "100"
  writeChan gm_player_ch "0"
  msg <- readChan player_gm_ch
  putStrLn $ "gm: score " ++ msg
  writeChan gm_init_ch "done"
  putStrLn "gm: <<<<DONE>>>>" 

--startRoll 1 player_roll_ch player_event_ch = do
--  writeChan player_event_ch "key"

--rollOrEnd "next" player_roll_ch player_event_ch = do
--  gen <- getStdGen
--  let num = take 1 (randomRs (toInteger 1, toInteger 3) gen)
--  putStrLn "roll: roll"
--  startRoll(num player_roll_ch player_event_ch)

roll ::Int -> String -> String -> Chan Msg -> Chan Msg -> IO ()
roll 1 healthStr keyStr player_roll_ch player_event_ch = do
  writeChan player_event_ch "roll"
  writeChan player_event_ch healthStr
  writeChan player_event_ch (show((read keyStr::Int)+1))
roll 2 healthStr keyStr player_roll_ch player_event_ch = do
  writeChan player_event_ch "roll"
  writeChan player_event_ch (show((read healthStr::Int)+50))
  writeChan player_event_ch keyStr
roll 3 healthStr keyStr player_roll_ch player_event_ch = do
  writeChan player_event_ch "damage"
  writeChan player_event_ch healthStr
  writeChan player_event_ch keyStr

rollProc player_roll_ch player_event_ch = do
  msg <- readChan player_roll_ch
  healthStr <- readChan player_roll_ch
  keyStr <- readChan player_roll_ch
--  let num = take 1 (randomRs (toInteger 1, toInteger 6) gen)
  let num = unsafePerformIO (getStdRandom (randomR (toInteger 1, toInteger 3)))
  putStrLn $ "roll: " ++ show(num)
  let numr = fromInteger num
  roll numr healthStr keyStr player_roll_ch player_event_ch
  rollProc player_roll_ch player_event_ch

enemyProc :: Chan Msg -> Chan Msg -> Int -> IO ()
enemyProc player_enemy_ch player_event_ch 0 = do
  state <- readChan player_enemy_ch
  pHealth <- readChan player_enemy_ch
  writeChan player_event_ch "dead"
  writeChan player_event_ch pHealth
  --let myHealth = health - 10
  enemyProc player_enemy_ch player_event_ch 30 
enemyProc player_enemy_ch player_event_ch health = do
  state <- readChan player_enemy_ch
  pHealth <- readChan player_enemy_ch
  writeChan player_event_ch "damage"
  writeChan player_event_ch (show((read pHealth::Int) - 10))
  let myHealth = health - 10
  enemyProc player_enemy_ch player_event_ch myHealth
  

playerLoop :: String -> Int -> Int -> Chan Msg -> Chan Msg -> Chan Msg -> Chan Msg -> IO ()
playerLoop state health 3 player_gm_ch player_roll_ch player_event_ch player_enemy_ch = do
  putStrLn "player: all keys"
  putStrLn $ "player: score " ++ (show(health))
  writeChan player_gm_ch (show(health))
playerLoop state 0 key player_gm_ch player_roll_ch player_event_ch player_enemy_ch = do
  writeChan player_gm_ch "-1"
playerLoop "dead" health key player_gm_ch player_roll_ch player_event_ch player_enemy_ch = do
  playerLoop ("roll") health key player_gm_ch player_roll_ch player_event_ch player_enemy_ch
playerLoop "damage" health key player_gm_ch player_roll_ch player_event_ch player_enemy_ch = do
  putStrLn "player: on attack"
  writeChan player_enemy_ch "damage"
  writeChan player_enemy_ch (show(health))
  --writeChan player_roll_ch (show(key))
  state <- readChan player_event_ch
  msg <- readChan player_event_ch
  let new_health = (read msg::Int)
  --msg <- readChan player_event_ch
  --let new_key = (read msg::Int)
  playerLoop state new_health key player_gm_ch player_roll_ch player_event_ch player_enemy_ch
playerLoop "roll" health key player_gm_ch player_roll_ch player_event_ch player_enemy_ch = do
  writeChan player_roll_ch "next"
  writeChan player_roll_ch (show(health))
  writeChan player_roll_ch (show(key))
  state <- readChan player_event_ch
  msg <- readChan player_event_ch
  let new_health = (read msg::Int)
  msg <- readChan player_event_ch
  let new_key = (read msg::Int)
  playerLoop state new_health new_key player_gm_ch player_roll_ch player_event_ch player_enemy_ch

playerProc gm_player_ch player_gm_ch player_roll_ch player_event_ch player_enemy_ch = do
  health <- readChan gm_player_ch
  key <- readChan gm_player_ch
  putStrLn "player: start"
  playerLoop ("roll") (read health::Int) (read key::Int) player_gm_ch player_roll_ch player_event_ch player_enemy_ch
  putStrLn "player: done?"

forkCreator action = do
  forkIO $ forever action

main :: IO ()
main = do
  
  init_gm_ch <- newChan
  gm_init_ch <- newChan
  gm_player_ch <- newChan
  player_gm_ch <- newChan
  player_roll_ch <- newChan
  player_event_ch <- newChan
  player_enemy_ch <- newChan

  forkCreator(playerProc gm_player_ch player_gm_ch player_roll_ch player_event_ch player_enemy_ch)
  forkCreator(gmProc init_gm_ch gm_init_ch gm_player_ch player_gm_ch)
  forkCreator(initProc init_gm_ch gm_init_ch)
  forkCreator(rollProc player_roll_ch player_event_ch)
  forkCreator(enemyProc player_enemy_ch player_event_ch 30)

  getLine
  return ()
