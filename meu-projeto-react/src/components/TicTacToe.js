import React, { useState } from 'react';

function Square({ value, onClick }) {
  return <button style={{ width: 60, height: 60 }} onClick={onClick}>{value}</button>;
}

function TicTacToe() {
  const [squares, setSquares] = useState(Array(9).fill(null));
  const [xIsNext, setXIsNext] = useState(true);

  const winner = calculateWinner(squares);

  const handleClick = (i) => {
    if (squares[i] || winner) return;
    const next = squares.slice();
    next[i] = xIsNext ? 'X' : 'O';
    setSquares(next);
    setXIsNext(!xIsNext);
  };

  return (
    <div>
      <h2>Jogo da Velha</h2>
      <div>{winner ? `Vencedor: ${winner}` : `Próximo: ${xIsNext ? 'X' : 'O'}`}</div>
      <div style={{ display: 'grid', gridTemplateColumns: 'repeat(3, 60px)' }}>
        {squares.map((sq, i) => (
          <Square key={i} value={sq} onClick={() => handleClick(i)} />
        ))}
      </div>
    </div>
  );
}

function calculateWinner(sq) {
  const lines = [[0,1,2],[3,4,5],[6,7,8],[0,3,6],[1,4,7],[2,5,8],[0,4,8],[2,4,6]];
  for (let [a,b,c] of lines) {
    if (sq[a] && sq[a] === sq[b] && sq[a] === sq[c]) return sq[a];
  }
  return null;
}

export default TicTacToe;
