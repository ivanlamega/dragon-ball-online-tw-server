CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1293;
	title = 129302;

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
				cont = 129308;
				gtype = 1;
				area = 129301;
				goal = 129304;
				grade = 132203;
				rwd = 100;
				sort = 129305;
				stype = 1;
				taid = 1;
				title = 129302;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 129307;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckLvl
			{
				maxlvl = 52;
				minlvl = 44;
			}
			CDboTSClickObject
			{
				objidx = "672;";
				widx = 1;
			}
			CDboTSCheckClrQst
			{
				and = "1292;";
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
			cont = 129308;
			gtype = 1;
			oklnk = 2;
			area = 129301;
			goal = 129304;
			sort = 129305;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 129302;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 129314;
			nextlnk = 254;
			rwdtbl = 129301;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 1752103;
			}
		}
	}
}

