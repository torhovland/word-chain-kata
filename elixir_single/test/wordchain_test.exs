defmodule WordChainTest do
  use ExUnit.Case

  import ElixirSingle.WordChain, only: [ wordChain: 3 ]

  test "blank words produce empty chain" do
    dictionary = ["foo"]
    assert wordChain(dictionary, "", "") |> length == 0
  end

  test "same start and end produce chain of length 1" do
    dictionary = ["foo"]
    assert wordChain(dictionary, "bar", "bar") == ["bar"]
  end

  test "neighbors produce chain of length 2" do
    dictionary = ["foo"]
    assert wordChain(dictionary, "bar", "baz") == ["bar", "baz"]
  end

  test "other words use dictionary to find a chain" do
    dictionary = ["boo", "foo", "fox"]
    assert wordChain(dictionary, "boo", "fox") == ["boo", "foo", "fox"]
  end
end
