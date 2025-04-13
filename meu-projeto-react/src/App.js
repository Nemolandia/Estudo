// src/App.js
import React from 'react';
import { BrowserRouter as Router, Routes, Route, Link } from 'react-router-dom';

import TodoList from './components/TodoList';
import ClickCounter from './components/ClickCounter';
import TicTacToe from './components/TicTacToe';
import Calculator from './components/Calculator';
import CepSearch from './components/CepSearch';

function App() {
  return (
    <Router>
      <div style={{ fontFamily: 'sans-serif' }}>
        <header style={{ backgroundColor: '#1e90ff', color: 'white', padding: '1rem' }}>
          <nav style={{ display: 'flex', gap: '1rem', flexWrap: 'wrap' }}>
            <Link to="/">To-Do List</Link>
            <Link to="/contador">Contador</Link>
            <Link to="/jogo">Jogo da Velha</Link>
            <Link to="/calculadora">Calculadora</Link>
            <Link to="/cep">Buscador de CEP</Link>
          </nav>
        </header>
        <main style={{ padding: '1rem' }}>
          <Routes>
            <Route path="/" element={<TodoList />} />
            <Route path="/contador" element={<ClickCounter />} />
            <Route path="/jogo" element={<TicTacToe />} />
            <Route path="/calculadora" element={<Calculator />} />
            <Route path="/cep" element={<CepSearch />} />
          </Routes>
        </main>
      </div>
    </Router>
  );
}

export default App;
