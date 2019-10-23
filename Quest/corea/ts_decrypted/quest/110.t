CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 110;
	title = 11002;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 100;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 11009;
				ctype = 1;
				idx = 3183104;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 11008;
				gtype = 1;
				area = 11001;
				goal = 11004;
				grade = 132203;
				rwd = 100;
				sort = 11005;
				stype = 2;
				taid = 1;
				title = 11002;
			}
		}
		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "2;";
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;1;252;";
			type = 0;
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "100;";
			type = 1;
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 11008;
			gtype = 1;
			oklnk = 2;
			area = 11001;
			goal = 11004;
			sort = 11005;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 11002;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 11014;
			nextlnk = 254;
			rwdtbl = 11001;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 3221203;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 11007;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 3183104;
			}
			CDboTSCheckPCRace
			{
				raceflg = 1;
			}
			CDboTSCheckPCCls
			{
				clsflg = 3;
			}
			CDboTSCheckLvl
			{
				maxlvl = 23;
				minlvl = 15;
			}
			CDboTSCheckClrQst
			{
				and = "109;";
			}
		}
	}
}

