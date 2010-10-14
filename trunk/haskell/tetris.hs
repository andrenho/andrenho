import Data.List
import Data.Maybe

data Status = No | RR
  deriving (Show, Eq)

data Direction = MDown | MLeft | MRight

data Piece = Piece {
    image :: PieceImage,
    rot :: Rotation,
    x :: Int,
    y :: Int } 
  deriving (Show)

data Rotation = D0 | D90 | D180 | D270
  deriving (Show)

data PieceImage = T
  deriving (Show)

type Board = [[Status]]

--
-- Piece
--
pieceImage :: PieceImage -> Rotation -> [[Status]]
pieceImage n rot = [[ No,RR,No,No ],
                    [ RR,RR,RR,No ],
                    [ No,No,No,No ],
                    [ No,No,No,No ]]

newPiece :: Piece
newPiece = Piece T D0 3 0


pieceH :: Piece -> Int
pieceH p = length (break (== [No,No,No,No]) (pieceImage (image p) (rot p)))


move :: Piece -> Direction -> Piece
move p MDown  = Piece (image p) (rot p) (x p) (y p + 1)
move p MLeft  = Piece (image p) (rot p) (x p - 1) (y p)
move p MRight = Piece (image p) (rot p) (x p + 1) (y p)


pieceOnEmptyBoard :: Piece -> Int -> Int -> Board
pieceOnEmptyBoard p w h = 
         take (y p) (repeat (take w (repeat No)))
      ++ map pieceOnLine (pieceImage (image p) (rot p))
      ++ take (h - (y p) - 4) (repeat (take w (repeat No)))
   where pieceOnLine ln = preW ++ ln ++ posW
         preW = (take (x p) (repeat No))
         posW = (take (w - (x p) - 4) (repeat No))


--
-- Board
--
makeBoard :: Int -> Int -> Board
makeBoard w h = take h (repeat (take w (repeat No)))


boardW :: Board -> Int
boardW b = length b


boardH :: Board -> Int
boardH b = (length . head) b


drawBoard :: Board -> String
drawBoard b = concat (map drawLine b)
        where drawLine ln = map drawChar ln ++ "\n"
              drawChar No = '.'
              drawChar RR = 'X'


--
-- Piece and board interaction
--
joinBoardAndPiece :: Board -> Piece -> Board
joinBoardAndPiece b p = zipWith merge b (pieceOnEmptyBoard p w h)
        where w = boardW b
              h = boardH b
              merge b p = zipWith mergeChar b p
              mergeChar b p = if b /= No then b else p


overlap :: Board -> Piece -> Bool
overlap b p = False


lockPiece :: Board -> Piece -> Board
lockPiece b p = b


-- 
-- Step
--
step :: Board -> Piece -> (Board, Piece)
step b p = if overlap b (move p MDown)
           then step (lockPiece b p) newPiece
           else (b, move p MDown)


b = makeBoard 8 12
p = Piece T D0 2 2
