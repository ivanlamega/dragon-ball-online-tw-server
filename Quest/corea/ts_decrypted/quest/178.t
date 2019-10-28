CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 178;
	title = 17802;

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
				conv = 17809;
				ctype = 1;
				idx = 7091101;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 17808;
				gtype = 1;
				area = 17801;
				goal = 17804;
				grade = 132203;
				rwd = 100;
				sort = 17805;
				stype = 1;
				taid = 1;
				title = 17802;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 17807;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckPCRace
			{
				raceflg = 1;
			}
			CDboTSClickNPC
			{
				npcidx = 7091101;
			}
			CDboTSCheckPCCls
			{
				clsflg = 1;
			}
			CDboTSCheckLvl
			{
				maxlvl = 28;
				minlvl = 20;
			}
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
		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "2;";
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 17808;
			gtype = 1;
			oklnk = 2;
			area = 17801;
			goal = 17804;
			sort = 17805;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 17802;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 17814;
			nextlnk = 254;
			rwdtbl = 17801;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 3031204;
			}
		}
	}
}

