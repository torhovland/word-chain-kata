defmodule ElixirSingle.WordChain do
  def wordChain(dictionary, "", "") do
    []
  end

  def wordChain(dictionary, startWord, endWord) when startWord == endWord do
    [startWord]
  end

  def wordChain(dictionary, startWord, endWord) do
    if areNeighbors(startWord, endWord) do
      [startWord, endWord]
 	  else
      processQueue(dictionary, [[startWord]], endWord)
    end
  end

  def processQueue(dictionary, [chain | tail], endWord) do
    [lastWord | _] = chain
    if lastWord == endWord do
      Enum.reverse chain
    else
      neighbors = addedNeighbors(dictionary, chain, endWord)
      processQueue(dictionary, tail ++ neighbors, endWord)
    end
  end

  def addedNeighbors(dictionary, chain, endWord) do
    [lastWord | _] = chain

    dictionary
    |> Enum.filter(&(areNeighbors &1, lastWord))
    |> Enum.map(&([&1 | chain]))
  end

  def fst ({x,_}) do
    x
  end

  def snd ({_,y}) do
    y
  end

  def areNeighbors(a, b) do
    if byte_size(a) != byte_size(b) do
      false
    else
      try do
        Enum.zip(to_char_list(a), to_char_list(b))
        |> Enum.filter(&((fst &1) != (snd &1)))
        |> Enum.count
        == 1
      catch
        :throw, value -> false
        what, value -> false
      end
    end
  end
end
