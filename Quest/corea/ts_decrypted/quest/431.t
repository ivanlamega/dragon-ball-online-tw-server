CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 431;
	title = 43102;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 100;
			prelnk = "1;";

			CDboTSActRegQInfo
			{
				cont = 43108;
				gtype = 0;
				area = 43101;
				goal = 43104;
				grade = 132203;
				rwd = 100;
				sort = 43105;
				stype = 1;
				taid = 1;
				title = 43102;
			}
			CDboTSActNPCConv
			{
				conv = 43109;
				ctype = 1;
				idx = 4261101;
				taid = 2;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 43107;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckPCRace
			{
				raceflg = 4;
			}
			CDboTSClickNPC
			{
				npcidx = 4261101;
			}
			CDboTSCheckLvl
			{
				maxlvl = 15;
				minlvl = 7;
			}
			CDboTSCheckClrQst
			{
				and = "430;";
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
			cont = 43108;
			gtype = 0;
			oklnk = 2;
			area = 43101;
			goal = 43104;
			sort = 43105;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 43102;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 43114;
			nextlnk = 254;
			rwdtbl = 43101;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4511304;
			}
		}
	}
}

