data Person = MkPerson { firstName :: String  
                     , age :: Int  
                     } deriving (Show)   

main = do
    let p = MkPerson { firstName = "Mike", age = 24}
    let older = p { age = 25 }
    print older
