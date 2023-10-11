#include <iostream>
#include <functional>
#include <numeric>
#include <optional>
#include <random>
#include <algorithm>
#include <map>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

using namespace std;
using namespace std::placeholders;

using Line = vector<char>;
using Board = vector<Line>;
using Lines = vector<Line>;

template<typename DestinationType>
auto transformAll = [](const auto& source, auto fn){
    DestinationType result;
    result.reserve(source.size());
    transform(source.begin(), source.end(), back_inserter(result), fn);
    return result;
};

auto toRange = [](const auto& collection){
    vector<int> range(collection.size());
    iota(begin(range), end(range), 0);
    return range;
};

auto accumulateAll = [](const auto source, auto fn){
    return accumulate(source.begin(), source.end(), typename decltype(source)::value_type(), fn);
};

auto all_of_collection = [](const auto& collection, auto fn){
    return all_of(collection.begin(), collection.end(), fn);
};

auto any_of_collection = [](const auto& collection, auto fn){
    return any_of(collection.begin(), collection.end(), fn);
};

auto lineToString = [](const auto& line){
    return transformAll<string>(line, [](auto const token) -> char { return token;});
};

auto boardToLinesString = [](const auto& board){
    return transformAll<vector<string>>(board, lineToString);
};

auto boardToString = [](const auto& board){
    const auto linesAsString = boardToLinesString(board);
    return accumulateAll(linesAsString, 
            [](string current, string lineAsString) { return current + lineAsString + "\n"; }
            );
};

auto concatenate = [](const auto& first, const auto& second){
    auto result{first};
    result.insert(result.end(), make_move_iterator(second.begin()), make_move_iterator(second.end()));
    return result;
};

auto concatenate3 = [](const auto& first, const auto& second, const auto& third){
    return concatenate(concatenate(first, second), third);
};

using Coordinate = pair<int, int>;

auto accessAtCoordinates = [](const auto& board, const Coordinate& coordinate){
    return board[coordinate.first][coordinate.second];
};

auto projectCoordinates = [](const auto& board, const auto& coordinates){
    const auto boardElementFromCoordinates = bind(accessAtCoordinates, board, _1);
    return transformAll<Line>(coordinates, boardElementFromCoordinates);
};

auto mainDiagonalCoordinates = [](const auto& board){
    const auto range = toRange(board);
    return transformAll<vector<Coordinate>>(range, [](const auto& index){return make_pair(index, index);});
};

auto secondaryDiagonalCoordinates = [](const auto& board){
    const auto range = toRange(board);
    return transformAll<vector<Coordinate>>(range, [board](auto index){return make_pair(index, board.size() - index - 1);});
};

auto columnCoordinates = [](const auto& board, const auto& columnIndex){
    const auto range = toRange(board);
    return transformAll<vector<Coordinate>>(range, [columnIndex](const auto& index){return make_pair(index, columnIndex);});
};

auto lineCoordinates = [](const auto& board, const auto& lineIndex){
    const auto range = toRange(board);
    return transformAll<vector<Coordinate>>(range, [lineIndex](const auto& index){return make_pair(lineIndex, index);});
};

auto mainDiagonal = [](const auto& board){
    return projectCoordinates(board, mainDiagonalCoordinates(board));
};

auto secondaryDiagonal = [](const auto& board){
    return projectCoordinates(board, secondaryDiagonalCoordinates(board));
};

auto column = [](const auto& board, const auto& columnIndex){
    return projectCoordinates(board, columnCoordinates(board, columnIndex));
};

auto line = [](const auto& board, const int lineIndex){
    return projectCoordinates(board, lineCoordinates(board, lineIndex));
};

auto allLines = [](const auto& board) {
    const auto range = toRange(board);
    return transformAll<Lines>(range, [board](auto index) { return line(board, index);});
};

auto allColumns = [](const auto& board) {
    const auto range = toRange(board);
    return transformAll<Lines>(range, [board](auto index) { return column(board, index);});
};

auto allDiagonals = [](const auto& board) -> Lines {
    return {mainDiagonal(board), secondaryDiagonal(board)};
};

template<typename SourceType, typename DestinationType>
auto applyAllLambdasToValue = [](const auto& fns, const auto& value){
    return transformAll<DestinationType>(fns, [value](const auto& fn){ return fn(value); } );
};

auto allLinesColumnsAndDiagonals = [](const auto& board) {
    return concatenate3(allLines(board), allColumns(board), allDiagonals(board));
};

auto lineFilledWith = [](const auto& line, const auto& tokenToCheck){
    return all_of_collection(line, [&tokenToCheck](const auto& token){ return token == tokenToCheck;});
};

auto lineFilledWithX = bind(lineFilledWith, _1, 'X'); 
auto lineFilledWithO = bind(lineFilledWith, _1, 'O');

template <typename CollectionBooleanOperation, typename CollectionProvider, typename Predicate>
auto booleanOperationOnProvidedCollection(CollectionBooleanOperation collectionBooleanOperation, CollectionProvider collectionProvider, Predicate predicate){
  return [=](auto collectionProviderSeed, auto predicateFirstParameter){
      return collectionBooleanOperation(collectionProvider(collectionProviderSeed), 
              bind(predicate, _1, predicateFirstParameter));
  };
}

auto tokenWins = booleanOperationOnProvidedCollection(any_of_collection, allLinesColumnsAndDiagonals, lineFilledWith);
auto xWins = bind(tokenWins, _1, 'X');
auto oWins = bind(tokenWins, _1, 'O');

/*auto xWins = [](const auto& board){
    return any_of_collection(allLinesColumnsAndDiagonals(board), lineFilledWithX);
};

auto oWins = [](const auto& board){
    return any_of_collection(allLinesColumnsAndDiagonals(board), lineFilledWithO);
};
*/

/* auto noneOf = [](const auto& collection, const auto& fn){
    return none_of(collection.begin(), collection.end(), fn);
};*/

// auto isEmpty = [](const auto& token){return token == ' ';};

auto isNotEmpty= [](const auto& token){return token != ' ';};

auto fullLine = bind(all_of_collection, _1, isNotEmpty);

auto full = [](const auto& board){
    return all_of_collection(board, fullLine);
};

auto draw = [](const auto& board){
    return full(board) && !xWins(board) && !oWins(board); 
};

auto inProgress = [](const auto& board){
    return !full(board) && !xWins(board) && !oWins(board); 
};

auto findInCollection = [](const auto& collection, const auto& fn){
    const auto result = find_if(collection.begin(), collection.end(), fn);
    return (result == collection.end()) ? nullopt : optional(*result);
};

auto findInCollectionWithDefault = [](const auto& collection, const auto& defaultResult, const auto& fn){
    const auto result = findInCollection(collection, fn);
    return result.has_value() ? (*result) : defaultResult;
}; 

auto howDidXWin = [](auto const board){
    map<string, Line> linesWithDescription{
        {"first line", line(board, 0)},
        {"second line", line(board, 1)},
        {"last line", line(board, 2)},
        {"first column", column(board, 0)},
        {"second column", column(board, 1)},
        {"last column", column(board, 2)},
        {"main diagonal", mainDiagonal(board)},
        {"secondary diagonal", secondaryDiagonal(board)},
        {"diagonal", secondaryDiagonal(board)},
    };
    auto xDidNotWin = make_pair("X did not win", Line{});
    auto xWon = [](auto value){
        return lineFilledWithX(value.second);
    };

    return findInCollectionWithDefault(linesWithDescription, xDidNotWin, xWon).first; 
};

// Checkmark 1
auto isValidBoard = [](const Board& board) -> bool 
{
    std::string stringifyBoard = boardToString(board);

    int countX = count(stringifyBoard.begin(), stringifyBoard.end(), 'X');
    int countO = count(stringifyBoard.begin(), stringifyBoard.end(), 'O');

    return (countX == 5 && countO == 4) || (countX == 4 && countO == 5);
};

auto generateShuffledLine = [](const int& remainingX)
{
    return [remainingX](const int& remainingO) -> std::tuple<int, int, Line> 
    {
        std::random_device rd;
        std::mt19937 g(rd());
        std::uniform_int_distribution<> distribute(0, std::min(remainingX, 3));

        int xCount = distribute(g);
        int oCount = 3 - xCount;

        int remainingX_copy = remainingX;
        int remainingO_copy = remainingO;

        if (xCount > remainingX) 
        {
            oCount += (xCount - remainingX);
            xCount = remainingX;
        }

        if (oCount > remainingO) 
        {
            xCount += (oCount - remainingO);
            oCount = remainingO;
        }

        Line generatedLine(xCount, 'X');
        generatedLine.insert(generatedLine.end(), oCount, 'O');
        std::shuffle(generatedLine.begin(), generatedLine.end(), g);

        remainingX_copy -= xCount;
        remainingO_copy -= oCount;

        return {remainingX_copy, remainingO_copy, generatedLine};
    };
};

auto generateValidBoard = []() -> Board 
{
    std::random_device rd;
    std::mt19937 g(rd());
    std::uniform_int_distribution<> totalDistribution(4, 5);

    int totalX = totalDistribution(g);
    int totalO = 9 - totalX;

    std::array<int, 3> indices = {0, 1, 2}; //placeholder

    auto generatedBoard = std::accumulate(indices.begin(), indices.end(), std::make_tuple(totalX, totalO, Board()), [&](const std::tuple<int, int, Board>& acc, const int) 
    {
            auto [currentX, currentO, currentBoard] = acc;

            auto [newX, newO, newLine] = generateShuffledLine(currentX)(currentO);
            currentBoard.push_back(newLine);

            return std::make_tuple(newX, newO, currentBoard);
    });

    auto [x_, y_, result] = generatedBoard;

    return result;
};

TEST_CASE("Generate Valid Board [Property Testing]") 
{
    Board generatedBoard = generateValidBoard();

    CHECK_EQ(true, isValidBoard(generatedBoard));
}

//Checkmark 2
auto isValidBoardWithoutInvalidTokens = [](const Board& board) -> bool 
{
    std::string stringifyBoard = boardToString(board);

    int countX = std::count(stringifyBoard.begin(), stringifyBoard.end(), 'X');
    int countO = std::count(stringifyBoard.begin(), stringifyBoard.end(), 'O');
    int countInvalidTokens = stringifyBoard.size() - countX - countO;
    
    return ((countX == 5 && countO == 4) || (countX == 4 && countO == 5)) && countInvalidTokens == 0;
};

auto generateErroneousShuffledLine = []() -> Line 
{
    std::random_device rd;
    std::mt19937 g(rd());

    std::uniform_int_distribution<> distributeASCII(33, 126);

    Line generatedLine(3);

    std::generate(generatedLine.begin(), generatedLine.end(), [&]() 
    {
        return static_cast<char>(distributeASCII(g));
    });

    std::shuffle(generatedLine.begin(), generatedLine.end(), g);

    return generatedLine;
};

auto generateInvalidBoard = []() -> Board 
{
    Board board;
    board.push_back(generateErroneousShuffledLine());
    board.push_back(generateErroneousShuffledLine());
    board.push_back(generateErroneousShuffledLine());

    return board;
};

TEST_CASE("Generate Invalid Board [Property Testing]") 
{
    Board generatedBoard = generateInvalidBoard();

    CHECK_EQ(false, isValidBoardWithoutInvalidTokens(generatedBoard));
}

//Checkmark 3
auto isValidPartiallyFilledBoard = [](const Board& board) -> bool 
{
    std::string currentStringified = boardToString(board);
    int countX = std::count(currentStringified.begin(), currentStringified.end(), 'X');
    int countO = std::count(currentStringified.begin(), currentStringified.end(), 'O');

    return std::abs(countX - countO) <= 1;
};

auto generatePartiallyFilledBoard = []() -> Board 
{
    Board board = generateValidBoard();

    std::random_device rd;
    std::mt19937 g(rd());

    std::uniform_int_distribution<> cellCountDist(1, 8);
    std::uniform_int_distribution<> rowDist(0, 2);
    std::uniform_int_distribution<> colDist(0, 2);

    int replaceCount = cellCountDist(g);

    std::vector<int> indices(replaceCount);
    std::iota(indices.begin(), indices.end(), 0);

    board = std::accumulate(indices.begin(), indices.end(), board, [&](const Board& acc, const int) 
    {
        Board copy_board = acc;

        int r = rowDist(g);
        int c = colDist(g);

        char originalValue = copy_board.at(r).at(c);
        copy_board.at(r).at(c) = ' ';

        std::string currentStringified = boardToString(copy_board);
        int countX = std::count(currentStringified.begin(), currentStringified.end(), 'X');
        int countO = std::count(currentStringified.begin(), currentStringified.end(), 'O');

        if (std::abs(countX - countO) > 1) {
            copy_board.at(r).at(c) = originalValue;
        }

        return copy_board;
    });

    return board;
};


TEST_CASE("Generate Invalid Board [Property Testing]") 
{
    Board generatedBoard = generatePartiallyFilledBoard();

    CHECK_EQ(true, isValidPartiallyFilledBoard(generatedBoard));
}

//Checkmark 4
auto generateInvalidBoardTwo = []() -> Board 
{
    std::random_device rd;
    std::mt19937 g(rd());
    std::uniform_int_distribution<> totalDistribution(0, 3);

    int totalX = totalDistribution(g);
    int totalO = 9 - totalX;

    std::array<int, 3> indices = {0, 1, 2}; //placeholder

    auto generatedBoard = std::accumulate(indices.begin(), indices.end(), std::make_tuple(totalX, totalO, Board()), [&](const std::tuple<int, int, Board>& acc, const int) 
    {
            auto [currentX, currentO, currentBoard] = acc;

            auto [newX, newO, newLine] = generateShuffledLine(currentX)(currentO);
            currentBoard.push_back(newLine);

            return std::make_tuple(newX, newO, currentBoard);
    });

    auto [x_, y_, result] = generatedBoard;

    return result;
};

auto generatePartiallyFilledInvalidBoard = []() -> Board 
{
    Board board = generateInvalidBoardTwo();

    std::random_device rd;
    std::mt19937 g(rd());

    std::uniform_int_distribution<> cellCountDist(1, 8);
    std::uniform_int_distribution<> rowDist(0, 2);
    std::uniform_int_distribution<> colDist(0, 2);

    int replaceCount = cellCountDist(g);

    std::vector<int> indices(replaceCount);
    std::iota(indices.begin(), indices.end(), 0);

    board = std::accumulate(indices.begin(), indices.end(), board, [&](const Board& acc, const int) 
    {
        Board copy_board = acc;

        int r = rowDist(g);
        int c = colDist(g);

        char originalValue = copy_board.at(r).at(c);
        copy_board.at(r).at(c) = ' ';

        if(isValidBoard(copy_board))
        {
            copy_board.at(r).at(c) = originalValue;
        }

        return copy_board;
    });

    return board;
};

TEST_CASE("Generate Partially Filled Invalid Board [Property Testing]") 
{
    Board generatedBoard = generatePartiallyFilledInvalidBoard();

    CHECK_EQ(false, isValidPartiallyFilledBoard(generatedBoard));
}

//Checkmark 5
auto setLine = [](const char& token) -> Line 
{
    return Line(3, token);
};

auto setColumn = [](const Board& board, const int columnIndex, const char& token) -> Board 
{
    Board modifiedBoard = board;

    std::transform(board.begin(), board.end(), modifiedBoard.begin(), [columnIndex, token](const Line& line) 
    {
        Line modifiedLine = line;
        modifiedLine[columnIndex] = token;
        return modifiedLine;
    });

    return modifiedBoard;
};


auto setDiagonal(const Board& board, const bool mainDiagonal, const char token) -> Board
{
    Board modifiedBoard = board;
    int position = 0;

    std::transform(board.begin(), board.end(), modifiedBoard.begin(), 
        [mainDiagonal, token, &position](const Line& line) 
        {
            Line updatedLine = line;
            if (mainDiagonal) 
            {
                updatedLine[position++] = token;
            }
            else 
            {
                updatedLine[2 - position++] = token;
            }

            return updatedLine;
        }
    );

    return modifiedBoard;
};

auto placeOpposingTokens = [](const Board& board, const char token) -> Board
{
    static std::random_device rd;
    static std::mt19937 g(rd());

    Board copy_board = board;

    std::vector<std::pair<int, int>> allPositions(3 * 3);

    int index = 0;
    std::generate(allPositions.begin(), allPositions.end(), [&index]() 
    {
        auto current = std::make_pair(index / 3, index % 3);
        ++index;
        return current;
    });

    std::transform(allPositions.begin(), allPositions.end(), allPositions.begin(), [](std::pair<int, int>& p) 
    {
        return std::make_pair(p.first / 3, p.second % 3);
    });

    std::vector<std::pair<int, int>> emptyPositions;

    std::copy_if(allPositions.begin(), allPositions.end(), std::back_inserter(emptyPositions), [&copy_board](const std::pair<int, int>& pos) 
    {
        return copy_board.at(pos.first).at(pos.second) == ' ';
    });

    std::shuffle(emptyPositions.begin(), emptyPositions.end(), g);

    copy_board.at(emptyPositions[0].first).at(emptyPositions[0].second) = token;
    copy_board.at(emptyPositions[1].first).at(emptyPositions[1].second) = token;

    return copy_board;
};


auto generateWinningBoard = []() -> Board 
{
    static std::random_device rd;
    static std::mt19937 g(rd());

    std::uniform_int_distribution<> typeDist(0, 2); // line, column, diagonal
    std::uniform_int_distribution<> indexDist(0, 2);
    std::uniform_int_distribution<> tokenDist(0, 1); // X or O

    char token = tokenDist(g) == 0 ? 'X' : 'O';
    char otherToken = (token == 'X') ? 'O' : 'X';
    int type = typeDist(g);
    int index = indexDist(g);

    Board board(3, Line(3, ' '));

    if (type == 0) 
    {
        board[index] = setLine(token);
    }
    else if (type == 1) 
    {
        board = setColumn(board, index, token);
    } 
    else 
    {
        board = setDiagonal(board, index == 0, token);
    }

    return placeOpposingTokens(board, otherToken);
};

auto hasPlayerWon = [](const Board& board, const char player) 
{
    // ROW
    if (std::any_of(board.begin(), board.end(), [player](const Line& line) 
    {
        return std::count(line.begin(), line.end(), player) == 3;
    }))
    {
        return true;
    }

    // COLUMN
    std::array<int, 3> columnIndices = {0, 1, 2};

    if (std::any_of(columnIndices.begin(), columnIndices.end(), [&board, player](int columnIndex) 
        {
            return std::count_if(board.begin(), board.end(), 
                [columnIndex, player](const Line& line) 
                {
                    return line[columnIndex] == player;
                }) == 3;
        }))
    {
        return true;
    }

    // MAIN DIAG
    if (std::all_of(board.begin(), board.end(), [player, &board](const Line& line) 
        {
            auto index = std::distance(board.begin(), std::find(board.begin(), board.end(), line));
            return line[index] == player;
        }))
    {
        return true;
    }

    // SECONDARY DIAG
    if (std::all_of(board.begin(), board.end(), [player, &board](const Line& line)
        {
            auto index = std::distance(board.begin(), std::find(board.begin(), board.end(), line));
            return line[2 - index] == player;
        }))
    {
        return true;
    }

    return false;
};

auto isWinningBoard = [](const Board& board) -> bool
{
    return hasPlayerWon(board, 'X') || hasPlayerWon(board, 'O');
};

TEST_CASE("Generate Winning Board [Property Testing]") 
{
    Board generatedBoard = generateWinningBoard();

    CHECK_EQ(true, isWinningBoard(generatedBoard));
}

TEST_CASE("lines"){
    Board board{
        {'X', 'X', 'X'},
        {' ', 'O', ' '},
        {' ', ' ', 'O'}
    };

    Line expectedLine0{'X', 'X', 'X'};
    CHECK_EQ(expectedLine0, line(board, 0));
    Line expectedLine1{' ', 'O', ' '};
    CHECK_EQ(expectedLine1, line(board, 1));
    Line expectedLine2{' ', ' ', 'O'};
    CHECK_EQ(expectedLine2, line(board, 2));
}

TEST_CASE("all columns"){
    Board board{
        {'X', 'X', 'X'},
        {' ', 'O', ' '},
        {' ', ' ', 'O'}
    };

    Line expectedColumn0{'X', ' ', ' '};
    CHECK_EQ(expectedColumn0, column(board, 0));
    Line expectedColumn1{'X', 'O', ' '};
    CHECK_EQ(expectedColumn1, column(board, 1));
    Line expectedColumn2{'X', ' ', 'O'};
    CHECK_EQ(expectedColumn2, column(board, 2));
}

TEST_CASE("main diagonal"){
    Board board {
        {'X', 'X', 'X'},
        {' ', 'O', ' '},
        {' ', ' ', 'O'}
    };

    Line expectedDiagonal{'X', 'O', 'O'};

    CHECK_EQ(expectedDiagonal, mainDiagonal(board));
}

TEST_CASE("secondary diagonal"){
    Board board {
        {'X', 'X', 'X'},
        {' ', 'O', ' '},
        {' ', ' ', 'O'}
    };

    Line expectedDiagonal{'X', 'O', ' '};

    CHECK_EQ(expectedDiagonal, secondaryDiagonal(board));
}


TEST_CASE("all lines, columns and diagonals"){
    Board board {
        {'X', 'X', 'X'},
        {' ', 'O', ' '},
        {' ', ' ', 'O'}
    };

    Lines expected{
        {'X', 'X', 'X'},
        {' ', 'O', ' '},
        {' ', ' ', 'O'},
        {'X', ' ', ' '},
        {'X', 'O', ' '},
        {'X', ' ', 'O'},
        {'X', 'O', 'O'},
        {'X', 'O', ' '}
    };

    auto all = allLinesColumnsAndDiagonals(board);
    CHECK_EQ(expected, all);
}

TEST_CASE("line to string"){
    Line line{
        ' ', 'X', 'O'
    };

    CHECK_EQ(" XO", lineToString(line));
}

TEST_CASE("board to lines string"){
    Board board{
        {'X', 'X', 'X'},
        {' ', 'O', ' '},
        {' ', ' ', 'O'}
    };
    vector<string> expected{
        "XXX",
        " O ",
        "  O"
    };

    CHECK_EQ(expected, boardToLinesString(board));
}

TEST_CASE("board to string"){
    Board board{
        {'X', 'X', 'X'},
        {' ', 'O', ' '},
        {' ', ' ', 'O'}
    };
    string expected{"XXX\n O \n  O\n"};

    CHECK_EQ(expected, boardToString(board));
}

TEST_CASE("Line filled with X"){
    Line line{'X', 'X', 'X'};

    CHECK(lineFilledWithX(line));
}

TEST_CASE("Line not filled with X"){
    CHECK(!lineFilledWithX(Line({'X', 'O', 'X'})));
    CHECK(!lineFilledWithX(Line({'X', ' ', 'X'})));
}

TEST_CASE("X wins"){
    Board board{
        {'X', 'X', 'X'},
        {' ', 'O', ' '},
        {' ', ' ', 'O'}
    };

    CHECK(xWins(board));
}

TEST_CASE("O wins"){
    Board board{
        {'X', 'O', 'X'},
        {' ', 'O', ' '},
        {' ', 'O', 'X'}
    };

    CHECK(oWins(board));
}

TEST_CASE("draw"){
    Board board{
        {'X', 'O', 'X'},
        {'O', 'O', 'X'},
        {'X', 'X', 'O'}
    };

    CHECK(draw(board));
}

TEST_CASE("in progress"){
    Board board{
        {'X', 'O', 'X'},
        {'O', ' ', 'X'},
        {'X', 'X', 'O'}
    };

    CHECK(inProgress(board));
}


TEST_CASE("how did X win"){
    Board board{
        {'X', 'X', 'X'},
        {' ', 'O', ' '},
        {' ', ' ', 'O'}
    };

    CHECK_EQ("first line", howDidXWin(board));
}

TEST_CASE("X did not win"){
    Board board{
        {'X', 'X', ' '},
        {' ', 'O', ' '},
        {' ', ' ', 'O'}
    };

    CHECK_EQ("X did not win", howDidXWin(board));
}

TEST_CASE("Project column"){
    Board board{
        {'X', 'X', 'X'},
        {' ', 'O', ' '},
        {' ', ' ', 'O'}
    };

    Line expected0{'X', ' ', ' '};
    CHECK_EQ(expected0, column(board, 0));
    Line expected1{'X', 'O', ' '};
    CHECK_EQ(expected1, column(board, 1));
    Line expected2{'X', ' ', 'O'};
    CHECK_EQ(expected2, column(board, 2));
}

TEST_CASE("Range"){
    Board board{
        {'X', 'X', 'X'},
        {' ', 'O', ' '},
        {' ', ' ', 'O'}
    };

    vector<int> expected = {0, 1, 2};
    CHECK_EQ(expected, toRange(board));
    CHECK_EQ(expected, toRange(board[0]));
}
