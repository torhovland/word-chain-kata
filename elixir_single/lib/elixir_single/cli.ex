defmodule ElixirSingle.CLI do
  import ExProf.Macro

  @moduledoc """
  Handle the command line parsing and the dispatch to
  the various functions.
  """

  def main(argv) do
    argv
      |> parse_args
      |> process_args
  end

  def process_args(:help) do
    IO.puts """
    usage: elixir_single <dictionary file> <start word> <end word>
    """
    System.halt(0)
 	end

  def do_profile(dictionary, startWord, endWord) do
    profile do
      ElixirSingle.WordChain.wordChain(dictionary, startWord, endWord)
    end
  end

  def process_args({ dictionaryFile, startWord, endWord, true }) do
    dictionary = read_lines(dictionaryFile)
    records = do_profile dictionary, startWord, endWord
    total_percent = Enum.reduce(records, 0.0, &(&1.percent + &2))
    IO.inspect "total = #{total_percent}"
  end

  def process_args({ dictionaryFile, startWord, endWord, _ }) do
    read_lines(dictionaryFile)
    |> ElixirSingle.WordChain.wordChain(startWord, endWord)
    |> Enum.join(", ")
    |> IO.puts
  end

  @doc """
  `argv` can be -h or --help, which returns :help.

  Otherwise it is Program <dictionary file> <start word> <end word>
  """
  def parse_args(argv) do
    parse = OptionParser.parse(argv, switches: [ help: :boolean], aliases:  [ h:    :help   ])

    case parse do
      { options, [dictionaryFile, startWord, endWord], _ } ->
        { dictionaryFile, startWord, endWord, options[:profile] }
      _ ->
        :help
    end
  end

  def read_lines(file) do
 	  File.read!(file)
      |> String.split
 	end
end
