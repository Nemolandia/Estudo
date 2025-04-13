import React, { useState } from 'react';

function CepSearch() {
  const [cep, setCep] = useState('');
  const [dados, setDados] = useState(null);

  const buscar = async () => {
    const res = await fetch(`https://viacep.com.br/ws/${cep}/json/`);
    const json = await res.json();
    setDados(json);
  };

  return (
    <div>
      <h2>Buscar CEP</h2>
      <input value={cep} onChange={(e) => setCep(e.target.value)} placeholder="Digite o CEP" />
      <button onClick={buscar}>Buscar</button>
      {dados && (
        <div>
          <p>Logradouro: {dados.logradouro}</p>
          <p>Bairro: {dados.bairro}</p>
          <p>Cidade: {dados.localidade}</p>
          <p>Estado: {dados.uf}</p>
        </div>
      )}
    </div>
  );
}

export default CepSearch;
