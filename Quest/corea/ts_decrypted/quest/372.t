CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 372;
	title = 37202;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 4;
			elnk = 255;
			nextlnk = 2;
			prelnk = "1;";

			CDboTSActMiniNarration
			{
				taid = 1;
				tidx = 3722;
			}
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 100;
			prelnk = "4;";

			CDboTSActNPCConv
			{
				conv = 37209;
				ctype = 1;
				idx = 4651201;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 37208;
				gtype = 0;
				area = 37201;
				goal = 37204;
				grade = 132203;
				rwd = 100;
				sort = 37205;
				stype = 2;
				taid = 1;
				title = 37202;
			}
		}
		CDboTSContUnifiedNarration
		{
			cancellnk = 1;
			cid = 3;
			idx = 3721;
			lilnk = 255;
			oklnk = 1;
			prelnk = "0;";
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 37207;
			nolnk = 253;
			rm = 0;
			yeslnk = 3;

			CDboTSCheckPCRace
			{
				raceflg = 2;
			}
			CDboTSClickNPC
			{
				npcidx = 4651201;
			}
			CDboTSCheckLvl
			{
				maxlvl = 28;
				minlvl = 20;
			}
			CDboTSCheckClrQst
			{
				and = "309;";
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
			cont = 37208;
			gtype = 0;
			oklnk = 4;
			area = 37201;
			goal = 37204;
			sort = 37205;
			prelnk = "3;3;";
			ds = 0;
			grade = 132203;
			rwd = 100;
			title = 37202;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 37214;
			nextlnk = 254;
			rwdtbl = 37201;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4751107;
			}
		}
	}
}

