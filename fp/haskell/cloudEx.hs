import Control.Concurrent(threadDelay)
import Data.Monoid ((<>))
import Data.String
import Data.Binary (Binary)
import Data.Typeable (Typeable)
import GHC.Generics
import Control.Distributed.Process
import Control.Distributed.Process.Closure
import Control.Distributed.Process.Node (initRemoteTable,newLocalNode,runProcess)
import System.Environment (getArgs)
import Network.Transport.TCP(createTransport, defaultTCPParameters)
import Control.Distributed.Process.Serializable
import Control.Monad (forever)
import System.Random
import System.IO.Unsafe
--computeLocalSocket :: String -> (String, String)
--computeLocalSocket serviceName = ("127.0.0.1", serviceName)

initProc :: Process()
initProc = do
  msg <- expect
  liftIO $ putStrLn $ "init: receive " ++ msg
  gmPid <- whereis "gm"
  case gmPid of
    Just actualPid -> do
      liftIO $ putStrLn "init: start"
      liftIO $ threadDelay 100
      send actualPid "i_start"
    Nothing -> do
      liftIO $ putStrLn "init: not found gm"
  res <- expect
  liftIO $ putStrLn $ "init: Score " ++ res

gmProc :: Process()
gmProc = do
  msg <- expect
  liftIO $ putStrLn $ "gm: receive " ++ msg

  playerPid <- whereis "player"
  case playerPid of
    Just actualPid -> do
      liftIO $ threadDelay 100
      send actualPid "100"
      send actualPid "0"
    Nothing -> do
      liftIO $ putStrLn "gm: player not found"

  score <- expect
  liftIO $ putStrLn $ "gm: receive " ++ score

  initPid <- whereis "init"
  case initPid of
    Just actualPid -> do
      liftIO $ threadDelay 100
      send actualPid score
    Nothing -> do
      liftIO $ putStrLn "gm: init not found"
  gmProc

roll :: Int -> Int -> Int -> Process()
roll 1 health key = do
  playerPid <- whereis "player"
  liftIO $ putStrLn "roll: key"
  case playerPid of
    Just actualPid -> do
      liftIO $ threadDelay 100
      send actualPid "roll"
      send actualPid (show(health))
      send actualPid (show(key + 1))
    Nothing -> do
      liftIO $ putStrLn "roll: player not found"
roll 2 health key = do
  playerPid <- whereis "player"
  liftIO $ putStrLn "roll: health"
  case playerPid of
    Just actualPid -> do
      liftIO $ threadDelay 100
      send actualPid "roll"
      send actualPid (show(health + 50))
      send actualPid (show(key))
    Nothing -> do
      liftIO $ putStrLn "roll: player not found"
roll 3 health key = do
  playerPid <- whereis "player"
  liftIO $ putStrLn "roll: enemy"
  case playerPid of
    Just actualPid -> do
      liftIO $ threadDelay 100
      send actualPid "damage"
      send actualPid (show(health))
      send actualPid (show(key))
    Nothing -> do
      liftIO $ putStrLn "roll: player not found"

rollProc :: Process()
rollProc = do
  msg <- expect
  liftIO $ putStrLn $ "roll: receive " ++ msg
  health <- expect
  key <- expect
  let num = unsafePerformIO (getStdRandom (randomR (toInteger 1, toInteger 3)))
  roll (fromInteger num) (read health::Int) (read key::Int)
  rollProc

enemyProc :: Int -> Process()
enemyProc 0 = do
  pHealth <- expect
  liftIO $ putStrLn $ "enemy: receive " ++ pHealth
  playerPid <- whereis "player"
  case playerPid of
    Just actualPid -> do
      liftIO $ putStrLn "enemy: damage"
      send actualPid "dead"
      send actualPid (pHealth)
      enemyProc 30
enemyProc health = do
  pHealth <- expect
  liftIO $ putStrLn $ "enemy: receive " ++ pHealth
  playerPid <- whereis "player"
  case playerPid of
    Just actualPid -> do
      liftIO $ putStrLn "enemy: damage"
      send actualPid "damage"
      send actualPid (show((read pHealth::Int) - 10))
      enemyProc (health - 10)

playerLoop :: String -> Int -> Int -> Process()
playerLoop state health 3 = do
  liftIO $ putStrLn "player: all keys"
  gmPid <- whereis "gm"
  case gmPid of
    Just actualPid -> do
      send actualPid (show(health))
playerLoop state 0 key = do
  gmPid <- whereis "gm"
  case gmPid of
    Just actualPid -> do
      send actualPid "-1"
playerLoop "dead" health key = do
  playerLoop ("roll") health key
playerLoop "damage" health key = do
  enemyPid <- whereis "enemy"
  case enemyPid of
    Just actualPid -> do
      send actualPid (show(health))
      state <- expect
      msg <- expect
      let new_health = (read msg::Int)
      playerLoop state new_health key
playerLoop "roll" health key = do
  rollPid <- whereis "roll"
  case rollPid of
    Just actualPid -> do
      send actualPid "next"
      send actualPid (show(health))
      send actualPid (show(key))
      state <- expect
      new_health <- expect
      new_key <- expect
      playerLoop state (read new_health::Int) (read new_key::Int)

playerProc :: Process()
playerProc = do
  health <- expect
  key <- expect
  liftIO $ putStrLn $ "player: receive " ++ health ++ " " ++ key
  playerLoop ("roll")  (read health::Int) (read key::Int)
--remotable ['spawnSess]
--remotable ['initProc, 'gmProc]


main :: IO ()
main = do
  let host = "127.0.0.1"
  let port = "10501"
 
  Right t <- createTransport host port (const (host,port)) defaultTCPParameters
  node <- newLocalNode t initRemoteTable
  runProcess node $ do
    us <- getSelfNode

    pidInit <- spawnLocal initProc
    register "init" pidInit

    pidGm <- spawnLocal gmProc
    register "gm" pidGm

    pidRoll <- spawnLocal rollProc
    register "roll" pidRoll

    pidEnemy <- spawnLocal (enemyProc 30)
    register "enemy" pidEnemy

    pidPlayer <- spawnLocal playerProc
    register "player" pidPlayer

    send pidInit "start"
    forever $ liftIO $ threadDelay 1000
