g x = 2 * x
h x = 3 * x

-- Where
f x 
    | x < 0 = g a  
    | otherwise = h a  
    where
        a = 5
