defmodule CliTest do
  use ExUnit.Case

  import ElixirSingle.CLI, only: [ parse_args: 1 ]

  test ":help returned by option parsing with -h and --help options" do
    assert parse_args(["-h",     "anything"]) == :help
    assert parse_args(["--help", "anything"]) == :help
  end

  test "three values returned if three given" do
    assert parse_args(["..\dictionary.txt", "cat", "bat"]) == { "..\dictionary.txt", "cat", "bat" }
  end
end
