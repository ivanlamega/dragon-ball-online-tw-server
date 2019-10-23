CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 219;
	title = 21902;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 101;
			elnk = 255;
			nextlnk = 254;
			prelnk = "100;";

			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 0;
				idx0 = 2312100;
				cnt0 = 8;
				cnt2 = 0;
				ectype = -1;
				etype = 1;
				idx1 = -1;
				taid = 1;
				esctype = 0;
				idx2 = -1;
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
			cid = 254;
			prelnk = "101;";
			type = 1;
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;252;1;";
			type = 0;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 21907;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckPCRace
			{
				raceflg = 2;
			}
			CDboTSClickNPC
			{
				npcidx = 4751301;
			}
			CDboTSCheckLvl
			{
				maxlvl = 12;
				minlvl = 4;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 21908;
			gtype = 2;
			oklnk = 2;
			area = 21901;
			goal = 21904;
			sort = 21905;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 21902;
		}
		CDboTSContGCond
		{
			cid = 3;
			prelnk = "2;";
			nolnk = 255;
			rm = 0;
			yeslnk = 100;

			CDboTSCheckSToCEvt
			{
				itype = 0;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 21914;
			nextlnk = 101;
			rwdtbl = 21901;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4751301;
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
				conv = 21909;
				ctype = 1;
				idx = 4751301;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 21908;
				gtype = 2;
				area = 21901;
				goal = 21904;
				m0fz = "-2166.000000";
				m0widx = 1;
				sort = 21905;
				stype = 1;
				m0fy = "0.000000";
				grade = 132203;
				m0fx = "3889.000000";
				m0ttip = 21915;
				rwd = 100;
				taid = 1;
				title = 21902;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 0;
				idx0 = 2312100;
				cnt0 = 6;
				cnt2 = 0;
				ectype = -1;
				etype = 0;
				idx1 = -1;
				taid = 3;
				esctype = 0;
				idx2 = -1;
			}
		}
	}
}

