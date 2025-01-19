#include "cell.h"

Cell::Cell()
    : m_isMine(false)
    , m_isRevealed(false)
    , m_adjacentMines(0)
    , m_row(0)
    , m_col(0)
{
}

bool Cell::isMine() const
{
    return m_isMine;
}

void Cell::setIsMine(bool isMine)
{
    m_isMine = isMine;
}

bool Cell::isRevealed() const
{
    return m_isRevealed;
}

void Cell::setIsRevealed(bool revealed)
{
    m_isRevealed = revealed;
}

bool Cell::isFlagged() const
{
    return m_isFlagged;
}

void Cell::flipFlag()
{
    m_isFlagged = !m_isFlagged;
}

int Cell::adjacentMines() const
{
    return m_adjacentMines;
}

void Cell::setAdjacentMines(int count)
{
    m_adjacentMines = count;
}

int Cell::row() const
{
    return m_row;
}
  