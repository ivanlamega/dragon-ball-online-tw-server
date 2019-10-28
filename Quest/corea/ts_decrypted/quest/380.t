CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 380;
	title = 38002;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGCond
		{
			cid = 3;
			prelnk = "2;";
			nolnk = 255;
			rm = 0;
			yeslnk = 100;

			CDboTSBindStone
			{
			}
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 3;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 38009;
				ctype = 1;
				idx = 4211101;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 38008;
				gtype = 1;
				area = 38001;
				goal = 38004;
				m0fz = "-2661.898926";
				m0widx = 1;
				sort = 38005;
				stype = 2;
				m0fy = "-43.973999";
				grade = 132203;
				m0fx = "3227.990967";
				m0ttip = 38015;
				rwd = 100;
				taid = 1;
				title = 38002;
			}
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "100;";
			type = 1;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 38014;
			nextlnk = 254;
			rwdtbl = 38001;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4211101;
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;1;252;";
			type = 0;
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 38008;
			gtype = 1;
			oklnk = 2;
			area = 38001;
			goal = 38004;
			sort = 38005;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 38002;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 38007;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 4211101;
			}
			CDboTSCheckPCRace
			{
				raceflg = 2;
			}
			CDboTSCheckLvl
			{
				maxlvl = 10;
				minlvl = 2;
			}
			CDboTSCheckClrQst
			{
				and = "203;";
			}
		}
		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "2;";
		}
	}
}

