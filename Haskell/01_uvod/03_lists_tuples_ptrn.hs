{-- List basic functions --}

2 : [1,3] -- add 2 to list: [2,1,3]
1 !! [1,3] -- return on index: 1 
[1,2] ++ [3,4] -- concat: [1,2,3,4]
concat [[1,2], [3,4]] -- concat: [1,2,3,4]
take 2 ['a'..] -- takes 2: [a,b]
drop 2 [1,2,3] -- drops 3 elem [3]
length [1,2] -- len of list: 2
null [] -- True if l is empty, False otw
head [1,2] -- head of list: 1
tail [1,2,3] -- tail of list
reverse [1,2,3] -- reverse: [3,2,1]
3 `elem` [1,2,3] -- is 3 in list?: True
"Hello " ++ ['w','o','r','l','d'] -- "Hello world"
zipped = zip [1,2] ['a','b'] -- zip -> [(1, a), (2, b)]
(a, b) = unzip zipped -- a: [1,2], b: ['a','b']
sum [1,2] {-- and --} product [1,2,3] 
replicate 2 5 -- Replicate 5 2 times [5,5]

myheadfunc :: [x] -> x
myheadfunc (x:_) = x -- Custom head func

mytailfunc :: [x] -> [x]
mytailfunc (_:xs) = xs -- Custom tail func

rightTriangles = [ (a,b,c) | 
                   c <- [1..10], b <- [1..c], a <- [1..b],
                                         a^2 + b^2 == c^2 ]

{-- Tuples can have different types --}
mytuple = (1, 'a', [1,2,3])
fst rightTriangles {- or -} snd rightTriangles
get5th (_,_,_,_,a,_,_,_,_,_) = -- returns 5th element in 10tuple

listRng :: Int -> Int -> [Int]
listRng a b = [a..b]

pairMax :: Ord p => (p, p) -> p
pairMax p | fst p > snd p = fst p
          | otherwise = snd p

{-- Pattern Matching --}
len [] = 0 -- Custom length function base case
len (_:xs) = 1 + (len xs) -- Custom length function

-- not pattern example
not -> Bool -> Bool
not True = False
not False = True

-- Custom && function
(&&) :: Bool -> Bool -> Bool
True && True = x 
_ && _ = False
-- Second way (better)
(&&) :: Bool -> Bool -> Bool
True && x = x 
False && _ = False
