main = do
    let it = take 5 $ iterate (^2) 2
    print it
    -- IO kutija koja ima String u sebi,
    -- na taj string primenimo reverse
    r <- fmap reverse getLine
    putStrLn r

mayFunc m = do
    x <- m
    let y = x^2
    let z = 3 * y
    return z
